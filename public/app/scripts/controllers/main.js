'use strict';

/**
 * @ngdoc function
 * @name chatApp.controller:MainCtrl
 * @description
 * # MainCtrl
 * Controller of the chatApp
 */
angular.module('chatApp')
  .controller('MainCtrl', ['$scope', 'Users', 'Messages', 'localStorageService', function ($scope, Users, Messages, localStorageService) {
    angular.extend($scope, {
      users: [],
      massages: [],
      countOnPage: 15,
      me: {},
      saveUser: function() {
        Users.add({
          name: $scope.user
        }, function(response) {
          if (angular.isDefined(response.error)) {
            console.error("[users].add: " + response.error);
          } else {
            console.log("[users].add: user_id=" + response.id);
            localStorageService.set('token', response.token);
            $scope.isLogged = true;
            load();
          }
        });
      },
      saveMessage: function() {
        Messages.add({
          data: $scope.message,
          token: localStorageService.get('token')
        }, function(response) {
          if (angular.isDefined(response.error)) {
            console.error("[messages].add: " + response.error);
          } else {
            console.log("[messages].add: message added");
            getMessages();
          }
        });
      },
      isLogged: false,
      logout: function() {
        this.isLogged = false;
        localStorageService.remove('token');
      }
    });

    var getUsers = function() {
      Users.get({
        token: localStorageService.get('token')
      }, function(response) {
        if (angular.isDefined(response.error)) {
          console.error("[users].get: " + response.error);
        } else {
          console.log("[users].get: |users|=" + response.users.length);
          $scope.users = response.users;
        }
      });
    };

    var getMe = function() {
      Users.me({
        token: localStorageService.get('token')
      }, function(response) {
        if (angular.isDefined(response.error)) {
          console.error("[users].me: " + response.error);
        } else {
          console.log("[users].me: me={name:" + response.user.name + '}');
          $scope.isLogged = true;
          $scope.me = response.user;
        }
      });
    };

    var getMessages = function() {
      Messages.get({
        token: localStorageService.get('token')
      }, function(response) {
        if (angular.isDefined(response.error)) {
          console.error("[messages].get: " + response.error);
        } else {
          console.log("[messages].get: |messages|=" + response.messages.length);
          var start = Math.max(0, response.messages.length - $scope.countOnPage);
          $scope.messages = response.messages.slice(start);
        }
      });
    };

    var load = function() {
      getMe();
      getUsers();
      getMessages();
    };

    load();

    setInterval(getUsers, 10000);
    setInterval(getMessages, 1000);

  }]);
