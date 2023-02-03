import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
# from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # stocks_owned = db.execute("SELECT symbol, SUM(shares) FROM transactions WHERE customer_id == :customer_id GROUP BY symbol",customer_id=session["user_id"])
    stocks_owned = []

    for i in range(len(stocks_owned)):
        if stocks_owned[i]['SUM(shares)'] == 0:
            del(stocks_owned[i])

    for stock in stocks_owned:
        stock['name'] = lookup(stock['symbol']['name'])
        stock['price'] = round(lookup(stock['symbol'])['price'], 2)
        stock['total'] = round(lookup(stock['symbol'])['price'] * stock['SUM(shares)'], 2)

    # Get the value of the portfolio
    stock_value = 0
    for stock in stocks_owned:
        stock_value += stock['total']

    cash = round(float(db.execute("SELECT cash FROM users WHERE id == :id", id = session["user_id"])[0]['cash']), 2)
    total = round(stock_value + cash, 2)

    return render_template('index.html', stocks_owned=stocks_owned, stock_value=stock_value, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        ticker = request.form.get("ticker")
        if not ticker:
            return apology("Please enter a stock", 403)
        if not get_quote:
            return apology("Symbol not found", 403)

        shares = request.form.get('shares')
        if not shares:
            return apology("Please enter a quantity", 403)
        if int(shares) < 0:
            return apology("Invalid quanity", 403)

        stock_price = get_quote["price"]
        total_price = price * int(shares)

        balance = db.execute("SELECT cash FROM users WHERE id == :id", id=session["user_id"])[0]

        if total_price > float(balance["cash"]):
            return apology("Insufficient funds")
        else:
            new_balance = float(balance["cash"] - total_price)
            db.execute("INSERT INTO transactions (customer_id, type, symbol, shares, PPS, Total_Amount) VALUES (:customer_id, :type, :symbol, :shares, :PPS, :Total_Amount)", customer_id=session["user_id"], type="Buy", symbol=symbol, shares=shares, PPS=current_price, Total_Amount=amount_due)

    return apology("TODO")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

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


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    return apology("TODO")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    username = request.form.get('username')
    password = request.form.get('password')
    password1 = request.form.get('password1')

    if request.method == "POST":
        # Check user input

        # Check if any of the fields are empty
        if not username:
            return apology('must provide username', 403)

        if not password:
            return apology('must provide password', 403)

        if not password1:
            return apology('must confirm password', 403)

        # Make sure passwords match
        if not password == password1:
            return apology('passwords must match', 403)


        # Make sure the user hasn't been registered already
        if len(db.execute("SELECT username FROM users WHERE username == :username", username=username)) == 0:
            # Generate secure password hash
            pass_hash = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)

            # Add user to the database
            db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=username, hash=pass_hash)
            return redirect("/")
        else:
            return apology("user already exists", 403)

    # Method = GET
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")
