'use strict';

/**
 * @ngdoc service
 * @name chatApp.Messages
 * @description
 * # Messages
 * Service in the chatApp.
 */
angular.module('chatApp')
  .service('Messages', ['$resource', 'Config', function ($resource, Config) {
    return $resource('/messages', {}, {
      add: {
        method: 'POST',
        url: Config.server+'/messages/add'
      }
    });
  }]);
