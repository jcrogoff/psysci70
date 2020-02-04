var express = require('express'),
    router = express.Router(),
	path = require('path'),
	passport = require('passport');

// router.use('/comments', require('./comments'))
router.use('/users', require('./users'))

// middleware that is specific to this router
// define the home page route

router.post('/login',
  passport.authenticate('local',{ successRedirect: '/',
                                   failureRedirect: '/login',
                                   failureFlash: true }),
  function(req, res) {
    // If this function gets called, authentication was successful.
    // `req.user` contains the authenticated user.
    res.redirect('/users/' + req.user.username);
  });


router.get('/', function(req, res) {
	res.sendFile(path.join(__dirname, '/../views/homepage.html'));
})

module.exports = router
