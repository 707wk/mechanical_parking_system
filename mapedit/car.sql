/*
Navicat MySQL Data Transfer

Source Server         : localhost_3306
Source Server Version : 50612
Source Host           : localhost:3306
Source Database       : car

Target Server Type    : MYSQL
Target Server Version : 50612
File Encoding         : 65001

Date: 2016-03-21 17:53:23
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `t_carinfo`
-- ----------------------------
DROP TABLE IF EXISTS `t_carinfo`;
CREATE TABLE `t_carinfo` (
  `idcard` varchar(255) NOT NULL COMMENT '车卡号',
  `plate` varchar(255) DEFAULT NULL COMMENT '车牌号',
  `start` timestamp NULL DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP COMMENT '入库时间',
  `end` timestamp NULL DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`idcard`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of t_carinfo
-- ----------------------------

-- ----------------------------
-- Table structure for `t_carlocation`
-- ----------------------------
DROP TABLE IF EXISTS `t_carlocation`;
CREATE TABLE `t_carlocation` (
  `idcard` varchar(255) NOT NULL COMMENT '车卡号',
  `plate` varchar(255) DEFAULT NULL COMMENT '车牌号',
  `carbarnid` int(11) DEFAULT NULL COMMENT '车库编号',
  `num` int(11) DEFAULT NULL,
  `rows` int(11) DEFAULT NULL COMMENT '第几行',
  `cols` int(11) DEFAULT NULL COMMENT '第几列',
  PRIMARY KEY (`idcard`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of t_carlocation
-- ----------------------------

-- ----------------------------
-- Table structure for `t_garageinfo`
-- ----------------------------
DROP TABLE IF EXISTS `t_garageinfo`;
CREATE TABLE `t_garageinfo` (
  `id` int(11) NOT NULL COMMENT '编号',
  `name` varchar(255) DEFAULT NULL COMMENT '车库名',
  `nowstatus` int(11) DEFAULT NULL COMMENT '现在状态',
  `oldstatus` int(11) DEFAULT NULL COMMENT '上一状态',
  `command` varchar(255) DEFAULT NULL COMMENT '正在执行的命令',
  `sumcar` int(11) DEFAULT NULL COMMENT '容量',
  `spendcar` int(11) DEFAULT NULL COMMENT '已存车量',
  `map_rows` int(11) DEFAULT '-1' COMMENT '第几行',
  `map_cols` int(11) DEFAULT '-1' COMMENT '第几列',
  `rows` int(11) DEFAULT NULL COMMENT '几行',
  `cols` int(11) DEFAULT NULL COMMENT '几列',
  `speedrows` double(11,3) DEFAULT NULL COMMENT '横向移动速度',
  `speedcols` double(11,3) DEFAULT NULL COMMENT '纵向移动速度',
  `map_queue` text COMMENT '位置列表',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of t_garageinfo
-- ----------------------------
INSERT INTO `t_garageinfo` VALUES ('1', '232', null, null, null, null, null, '-1', '-1', '3', '2', '3.000', '4.000', '1 2 131075 ');
INSERT INTO `t_garageinfo` VALUES ('2', '34we', null, null, null, null, null, '-1', '-1', '3', '2', '3.000', '4.000', '131073 ');

-- ----------------------------
-- Table structure for `t_history`
-- ----------------------------
DROP TABLE IF EXISTS `t_history`;
CREATE TABLE `t_history` (
  `time` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00' ON UPDATE CURRENT_TIMESTAMP COMMENT '当前时间',
  `idcard` varchar(100) DEFAULT NULL COMMENT '卡号',
  `plate` varchar(100) DEFAULT NULL COMMENT '车牌',
  `name` varchar(100) DEFAULT NULL COMMENT '车主姓名',
  `timestatus` int(11) DEFAULT NULL COMMENT '存车:1 取车:2 充值:3',
  `carbarnid` int(11) DEFAULT NULL COMMENT '车库编号',
  `carbarnname` varchar(255) DEFAULT NULL COMMENT '车库名',
  `rows` int(11) DEFAULT NULL COMMENT '第几行',
  `cols` int(11) DEFAULT NULL COMMENT '第几列',
  `money` double DEFAULT NULL COMMENT '充值/扣除费用',
  `balance` double DEFAULT NULL COMMENT '余额',
  PRIMARY KEY (`time`),
  KEY `plate` (`plate`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of t_history
-- ----------------------------

-- ----------------------------
-- Table structure for `t_idtoplatenumber`
-- ----------------------------
DROP TABLE IF EXISTS `t_idtoplatenumber`;
CREATE TABLE `t_idtoplatenumber` (
  `idcard` int(11) NOT NULL DEFAULT '0' COMMENT '车卡号',
  `plate` varchar(255) DEFAULT NULL COMMENT '车牌号',
  `username` varchar(255) DEFAULT NULL,
  `phone` varchar(255) DEFAULT NULL,
  `balance` double DEFAULT NULL COMMENT '余额',
  PRIMARY KEY (`idcard`),
  KEY `plate_number` (`plate`) USING HASH
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of t_idtoplatenumber
-- ----------------------------

-- ----------------------------
-- Table structure for `t_map`
-- ----------------------------
DROP TABLE IF EXISTS `t_map`;
CREATE TABLE `t_map` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `x` int(11) NOT NULL,
  `y` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `type_id` int(11) NOT NULL,
  `value` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=197 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_map
-- ----------------------------
INSERT INTO `t_map` VALUES ('172', '2', '1', '4', '0', null);
INSERT INTO `t_map` VALUES ('173', '3', '1', '4', '0', null);
INSERT INTO `t_map` VALUES ('175', '3', '2', '4', '0', null);
INSERT INTO `t_map` VALUES ('176', '3', '3', '4', '0', null);
INSERT INTO `t_map` VALUES ('177', '3', '4', '4', '0', null);
INSERT INTO `t_map` VALUES ('178', '3', '5', '4', '0', null);
INSERT INTO `t_map` VALUES ('179', '3', '6', '4', '0', null);
INSERT INTO `t_map` VALUES ('180', '3', '7', '4', '0', null);
INSERT INTO `t_map` VALUES ('181', '3', '8', '4', '0', null);
INSERT INTO `t_map` VALUES ('182', '3', '9', '4', '0', null);
INSERT INTO `t_map` VALUES ('184', '2', '2', '4', '0', null);
INSERT INTO `t_map` VALUES ('186', '4', '7', '2', '3', '12');
INSERT INTO `t_map` VALUES ('187', '2', '8', '1', '4', '123q');
INSERT INTO `t_map` VALUES ('188', '3', '10', '4', '0', '');
INSERT INTO `t_map` VALUES ('190', '2', '10', '4', '0', '');
INSERT INTO `t_map` VALUES ('191', '1', '10', '4', '0', '');
INSERT INTO `t_map` VALUES ('192', '1', '11', '4', '0', '');
INSERT INTO `t_map` VALUES ('196', '2', '4', '3', '2', null);

-- ----------------------------
-- Table structure for `t_reservation`
-- ----------------------------
DROP TABLE IF EXISTS `t_reservation`;
CREATE TABLE `t_reservation` (
  `idcard` int(11) NOT NULL DEFAULT '0' COMMENT '车卡号',
  `plate` varchar(255) DEFAULT NULL COMMENT '车牌号',
  PRIMARY KEY (`idcard`),
  KEY `plate_number` (`plate`) USING HASH
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of t_reservation
-- ----------------------------

-- ----------------------------
-- Table structure for `t_user`
-- ----------------------------
DROP TABLE IF EXISTS `t_user`;
CREATE TABLE `t_user` (
  `name` varchar(255) DEFAULT NULL,
  `password` varchar(255) DEFAULT NULL,
  `type` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of t_user
-- ----------------------------
