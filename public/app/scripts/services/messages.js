'use strict';

/**
 * @ngdoc service
 * @name tcpserverApp.Messages
 * @description
 * # Messages
 * Service in the tcpserverApp.
 */
angular.module('tcpserverApp')
  .service('Messages', ['$resource', 'Config', function ($resource, Config) {
    return $resource('/messages', {}, {
      add: {
        method: 'POST',
        url: Config.server+'/messages/add'
      }
    });
  }]);
