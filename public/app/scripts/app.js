'use strict';

/**
 * @ngdoc overview
 * @name tcpserverApp
 * @description
 * # tcpserverApp
 *
 * Main module of the application.
 */
angular
  .module('tcpserverApp', [
    'ngResource',
    'ngRoute'
  ])
  .config(function ($routeProvider) {
    $routeProvider
      .when('/', {
        templateUrl: 'views/main.html',
        controller: 'MainCtrl'
      })
      .when('/about', {
        templateUrl: 'views/about.html',
        controller: 'AboutCtrl'
      })
      .otherwise({
        redirectTo: '/'
      });
  });
