import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    portfolio = db.execute("SELECT symbol, SUM(shares) as shareAmount, price FROM transactions WHERE user_id = :user_id GROUP BY symbol", user_id=session["user_id"])
    rows = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
    availableCash = rows[0]["cash"]
    return render_template("index.html", availableCash=availableCash, portfolio=portfolio)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        stock = lookup(request.form.get("symbol"))
        if stock == None:
            return apology("Please insert a correct ticker symbol")
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Please input a number")
        if shares < 0:
            return apology("Please input a positive number")
        rows = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
        availableCash = rows[0]["cash"]
        price = stock["price"]
        totalPrice = shares * price
        if availableCash < totalPrice:
            return apology("Not enough funds")
        db.execute("UPDATE users SET cash = cash - :totalPrice WHERE id = :user_id", user_id=session["user_id"], totalPrice=totalPrice)
        db.execute("INSERT INTO 'transactions' (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)", user_id=session["user_id"], symbol=request.form.get("symbol"), price=price, shares=shares)
        return redirect("/")
    elif request.method == "GET":
        return render_template("buy.html")

@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""
    username = request.form.get("username")
    if (len(db.execute("SELECT * FROM users WHERE username = :username", username=username)) == 0) or (len(username) >= 1):
        return jsonify(True)
    else:
        return jsonify(False)

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT symbol, shares, price, timestamp FROM transactions WHERE user_id = :user_id", user_id=session["user_id"])
    return render_template("history.html", transactions=transactions)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")

@app.route("/changepassword", methods=["GET", "POST"])
def changepassword():
    """Change password of user"""
    if request.method == "POST":
        if not request.form.get("username") and not request.form.get("password") and not request.form.get("newPassword"):
            return apology("Please fill in all fields")
        elif not request.form.get("username"):
            return apology("Please provide a username")
        elif not request.form.get("password") or not request.form.get("newPassword"):
            return apology("Please provide a password in the Password fields")
        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)
        hash = generate_password_hash(request.form.get("newPassword"))
        db.execute("UPDATE users SET hash = :hash WHERE id = :user_id", user_id=session["user_id"], hash=hash)
        return render_template("login.html")
    elif request.method == "GET":
        return render_template("changepassword.html")

@app.route("/addcash", methods=["GET", "POST"])
@login_required
def addcash():
    """Add cash to user"""
    if request.method == "POST":
        try:
            addCash = int(request.form.get("addCash"))
        except:
            return apology("Please input a number")
        if addCash < 0:
            return apology("Please input a positive number")
        rows = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
        db.execute("UPDATE users SET cash = cash + :addCash WHERE id = :user_id", user_id=session["user_id"], addCash=addCash)
        return redirect("/")
    elif request.method == "GET":
        return render_template("addcash.html")

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    elif request.method == "POST":
        #Get stock information
        stock = lookup(request.form.get("symbol"))
        #Validate ticker symbol
        if stock != None:
            return render_template("quoted.html", stock=stock)
        else:
            return apology("Please enter a valid stock symbol")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        if not request.form.get("username") and not request.form.get("password") and not request.form.get("confirmation"):
            return apology("Please fill in all fields")
        elif not request.form.get("username"):
            return apology("Please provide a username")
        elif not request.form.get("password") or not request.form.get("confirmation"):
            return apology("Please provide a password in Password and Confirm Password fields")
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Password and Confirm password fields do not match")
        hash = generate_password_hash(request.form.get("password"))
        addition = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username = request.form.get("username"), hash=hash)
        if not addition:
            return apology("The username already exists")
        else:
            return render_template("login.html")
    elif request.method == "GET":
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        stock = lookup(request.form.get("symbol"))
        if stock == None:
            return apology("Please select the appropriate stock")
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Please input a number")
        if shares < 0:
            return apology("Please input a positive number")
        sharesAvailable = db.execute("SELECT SUM(shares) as totalShares FROM transactions WHERE user_id = :user_id and symbol = :symbol GROUP BY symbol", symbol=request.form.get("symbol"), user_id=session["user_id"])
        if sharesAvailable[0]["totalShares"] < 1 or shares > sharesAvailable[0]["totalShares"]:
            return apology("Please input correct amount of shares to sell")
        price = stock["price"]
        totalPrice = shares * price
        db.execute("UPDATE users SET cash = cash + :totalPrice WHERE id = :user_id", user_id=session["user_id"], totalPrice=totalPrice)
        db.execute("INSERT INTO 'transactions' (user_id, symbol, shares, price) VALUES(:user_id, :symbol, :shares, :price)", user_id=session["user_id"], symbol=request.form.get("symbol"), shares=-shares, price=price)
        return redirect("/")
    elif request.method == "GET":
        stocksAvailable = db.execute("SELECT symbol, SUM(shares) as totalShares FROM transactions WHERE user_id = :user_id GROUP BY symbol", user_id=session["user_id"])
        return render_template("sell.html", stocksAvailable=stocksAvailable)

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
