'use strict';

/**
 * @ngdoc service
 * @name tcpserverApp.Users
 * @description
 * # Users
 * Service in the tcpserverApp.
 */
angular.module('tcpserverApp')
  .service('Users', ['$resource', 'Config', function ($resource, Config) {
    return $resource('/users', {}, {
      add: {
        method: 'POST',
        url: Config.server+'/users/add'
      }
    });
  }]);
