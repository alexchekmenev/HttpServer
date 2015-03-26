'use strict';

/**
 * @ngdoc service
 * @name chatApp.Config
 * @description
 * # Config
 * Constant in the chatApp.
 */
angular.module('chatApp')
  .constant('Config', {
    server: "",//http://localhost:"+this.port,
    port: 8030
  });
