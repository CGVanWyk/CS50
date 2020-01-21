import cs50
import re
import os
from flask import Flask, abort, redirect, render_template, request
from flask import send_file
from html import escape
from werkzeug.exceptions import default_exceptions, HTTPException
from werkzeug import secure_filename
from helpers import midlands, klinicare, rentmeester

# Web app
app = Flask(__name__)

@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/")
def index():
    """Handle requests for / via GET (and POST)"""
    fileName = ""
    return render_template("index.html")

@app.route("/processed", methods=["GET", "POST"])
def processed():
    """Handle requests for /process via GET and POST"""
    # Upload file
    if not request.files["file"]:
        return render_template("inputFile.html")
    try:
        file = request.files["file"]
        if not file:
            return render_template("inputFile.html")
        file.save(secure_filename(file.filename))
    except Exception:
        return render_template("inputFile.html")
    # Default definition of fileName
    fileName = "Error.txt"
    # Process files
    if not request.form.get("algorithm"):
        return render_template("inputMethod.html")
    elif request.form.get("algorithm") == "midlands":
        fileName = midlands(file.filename)
        if fileName == "Error.txt":
            return render_template("failure.html")
        else:
            #Returns a webpage after successfully processing the file
            return render_template("success.html", fileName=fileName)
        #return send_file(fileName, as_attachment=True, attachment_filename = fileName)
    elif request.form.get("algorithm") == "klinicare":
        fileName = klinicare(file.filename)
        if fileName == "Error.txt":
            return render_template("failure.html")
        else:
            #Returns a webpage after successfully processing the file
            return render_template("success.html", fileName=fileName)
        #return send_file(fileName, as_attachment=True, attachment_filename = fileName)
    elif request.form.get("algorithm") == "rentmeester":
        fileName = rentmeester(file.filename)
        if fileName == "Error.txt":
            return render_template("failure.html")
        else:
            #Returns a webpage after successfully processing the file
            return render_template("success.html", fileName=fileName)
        #return send_file(fileName, as_attachment=True, attachment_filename = fileName)
    else:
        return render_template("inputMethod.html")

@app.route("/<fileName>")
def download(fileName):
    return send_file(fileName, as_attachment=True, attachment_filename = fileName)