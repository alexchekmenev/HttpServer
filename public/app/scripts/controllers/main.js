'use strict';

/**
 * @ngdoc function
 * @name tcpserverApp.controller:MainCtrl
 * @description
 * # MainCtrl
 * Controller of the tcpserverApp
 */
angular.module('tcpserverApp')
  .controller('MainCtrl', ['$scope', 'Users', 'Messages', 'localStorageService', function ($scope, Users, Messages, localStorageService) {
    $scope.users = [];
    $scope.messages = [];

    var token = localStorageService.get('token');
    var K = 10;

    var getUsers = function() {
      var users = [];
      Users.get({
        token: token
      }, function(response) {
        if (angular.isDefined(response.error)) {
          console.error("[users].get: " + response.error);
        } else {
          console.log("[users].get: |users|=" + response.users.length);
          $scope.users = response.users;
        }
      });
    };

    var getMessages = function() {
      var messages = [];
      Messages.get({
        token: token
      }, function(response) {
        if (angular.isDefined(response.error)) {
          console.error("[messages].get: " + response.error);
        } else {
          console.log("[messages].get: |messages|=" + response.messages.length);
          $scope.messages = response.messages.slice(Math.max(0, response.messages.length - K));
        }
      });
    };

    $scope.saveUser = function() {
      Users.add({
        name: $scope.user
      }, function(response) {
        if (angular.isDefined(response.error)) {
          console.error("[users].add: " + response.error);
        } else {
          console.log("[users].add: user_id=" + response.id);
          token = response.token;
          localStorageService.set('token', token);
          getUsers();
        }
      });
    };

    $scope.saveMessage = function() {
      Messages.add({
        data: $scope.message,
        token: token
      }, function(response) {
        if (angular.isDefined(response.error)) {
          console.error("[messages].add: " + response.error);
        } else {
          console.log("[messages].add: message added");
          getMessages();
        }
      });
    };

    getUsers();
    getMessages();

    setInterval(getUsers, 10000);
    setInterval(getMessages, 1000);

  }]);
