/*
Navicat MySQL Data Transfer

Source Server         : car
Source Server Version : 50612
Source Host           : localhost:3306
Source Database       : car

Target Server Type    : MYSQL
Target Server Version : 50612
File Encoding         : 65001

Date: 2015-09-23 13:18:04
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `t_carinfo`
-- ----------------------------
DROP TABLE IF EXISTS `t_carinfo`;
CREATE TABLE `t_carinfo` (
  `id` int(11) NOT NULL,
  `plate_number` text,
  `balance` double(11,2) DEFAULT NULL,
  `mac` int(11) DEFAULT NULL,
  `rows` int(11) DEFAULT NULL,
  `cols` int(11) DEFAULT NULL,
  `start` timestamp NULL DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP,
  `end` timestamp NULL DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of t_carinfo
-- ----------------------------

-- ----------------------------
-- Table structure for `t_garageinfo`
-- ----------------------------
DROP TABLE IF EXISTS `t_garageinfo`;
CREATE TABLE `t_garageinfo` (
  `mac` int(11) NOT NULL,
  `map_rows` int(11) DEFAULT NULL,
  `map_cols` int(11) DEFAULT NULL,
  `rows` int(11) DEFAULT NULL,
  `cols` int(11) DEFAULT NULL,
  `speedrows` double(11,3) DEFAULT NULL,
  `speedcols` double(11,3) DEFAULT NULL,
  `sumcar` int(11) DEFAULT NULL,
  `spendcar` int(11) DEFAULT NULL,
  `map_queue` text,
  PRIMARY KEY (`mac`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of t_garageinfo
-- ----------------------------

-- ----------------------------
-- Table structure for `t_mapinfo`
-- ----------------------------
DROP TABLE IF EXISTS `t_mapinfo`;
CREATE TABLE `t_mapinfo` (
  `rows` int(11) DEFAULT NULL,
  `cols` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of t_mapinfo
-- ----------------------------

-- ----------------------------
-- Table structure for `t_maplocation`
-- ----------------------------
DROP TABLE IF EXISTS `t_maplocation`;
CREATE TABLE `t_maplocation` (
  `rows` int(11) NOT NULL DEFAULT '0',
  `cols` int(11) NOT NULL DEFAULT '0',
  `object` int(11) DEFAULT NULL,
  PRIMARY KEY (`rows`,`cols`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of t_maplocation
-- ----------------------------
