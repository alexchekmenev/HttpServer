'use strict';

/**
 * @ngdoc service
 * @name tcpserverApp.Config
 * @description
 * # Config
 * Constant in the tcpserverApp.
 */
angular.module('tcpserverApp')
  .constant('Config', {
    server: "",//http://localhost:"+this.port,
    port: 8030
  });
