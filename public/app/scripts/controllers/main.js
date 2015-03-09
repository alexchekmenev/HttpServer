'use strict';

/**
 * @ngdoc function
 * @name tcpserverApp.controller:MainCtrl
 * @description
 * # MainCtrl
 * Controller of the tcpserverApp
 */
angular.module('tcpserverApp')
  .controller('MainCtrl', function ($scope, $resource) {
    $scope.users = [];

    var apiEntryPoint = 'http://localhost:3030';

    var users = $resource('/users', {}, {
        get: {
            method: 'GET'
        },
        add: {
            method: 'POST',
            url: apiEntryPoint+'/users/add'
        }
    });
    users.get({}, function(users, headers) {
        console.log(users);
    })
  });
