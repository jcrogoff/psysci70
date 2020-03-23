// server.js

// BASE SETUP
// =============================================================================

// call the packages we need
const express = require('express'); // call express
const app = express(); // define our app using express
const bodyParser = require('body-parser');
const path = require('path');
var passport = require('passport'),
  LocalStrategy = require('passport-local').Strategy;

// configure app to use bodyParser()
// this will let us get the data from a POST

app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());
app.use(express.static(path.join(__dirname, 'public')));
app.use(express.static(path.join(__dirname, 'static')));
// passport config
passport.serializeUser(function(user, done) {
  done(null, user.id);
});

passport.deserializeUser(function(id, done) {
  User.findById(id, function(err, user) {
    done(err, user);
  });
});

var port = process.env.PORT || 8080; // set our port

// ROUTES FOR OUR API
// =============================================================================

// more routes for our API will happen here

// view homepage at http://localhost:8080

app.get('/', function(req, res) {
  res.sendFile(path.join(__dirname + '/views/homepage.html'));
});
app.get('/about', function(req, res) {
  res.sendFile(path.join(__dirname + '/views/about.html'));
});
app.get('/assign1', function(req, res) {
  res.sendFile(path.join(__dirname + '/views/assign1.html'));
});
app.get('/assign2', function(req, res) {
  res.sendFile(path.join(__dirname + '/views/assign2.html'));
});
app.get('/assign3', function(req, res) {
  res.sendFile(path.join(__dirname + '/views/assign3.html'));
});
app.get('/assign4', function(req, res) {
  res.sendFile(path.join(__dirname + '/views/assign4.html'));
});
app.get('/assign5', function(req, res) {
  res.sendFile(path.join(__dirname + '/views/assign5.html'));
});
app.get('/assign6', function(req, res) {
  res.sendFile(path.join(__dirname + '/views/assign6.html'));
});

// REGISTER OUR ROUTES -------------------------------
// import router config
app.use(require('./router'));

// START THE SERVER
// =============================================================================
app.listen(port);
console.log('PSYSCI website is running on port ' + port);
