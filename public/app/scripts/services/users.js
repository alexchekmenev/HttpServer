'use strict';

/**
 * @ngdoc service
 * @name chatApp.Users
 * @description
 * # Users
 * Service in the chatApp.
 */
angular.module('chatApp')
  .service('Users', ['$resource', 'Config', function ($resource, Config) {
    return $resource('/users', {}, {
      add: {
        method: 'POST',
        url: Config.server+'/users/add'
      },
      me: {
        method: 'GET',
        url: Config.server+'/users/me'
      }
    });
  }]);
