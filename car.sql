/*
Navicat MySQL Data Transfer

Source Server         : localhost_3306
Source Server Version : 50617
Source Host           : localhost:3306
Source Database       : car

Target Server Type    : MYSQL
Target Server Version : 50617
File Encoding         : 65001

Date: 2016-06-12 18:06:42
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `t_carinfo`
-- ----------------------------
DROP TABLE IF EXISTS `t_carinfo`;
CREATE TABLE `t_carinfo` (
  `plate` varchar(255) NOT NULL COMMENT '车牌号',
  `start` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00' ON UPDATE CURRENT_TIMESTAMP COMMENT '入库时间',
  `end` timestamp NULL DEFAULT '0000-00-00 00:00:00',
  `carbarnid` int(11) DEFAULT NULL COMMENT '车库编号',
  `num` int(11) DEFAULT NULL COMMENT '车位编号',
  `rows` int(11) DEFAULT NULL COMMENT '第几行',
  `cols` int(11) DEFAULT NULL COMMENT '第几列',
  PRIMARY KEY (`plate`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_carinfo
-- ----------------------------
INSERT INTO `t_carinfo` VALUES ('1', '2016-05-23 10:35:10', '2016-05-23 10:35:10', '2', '1', null, null);
INSERT INTO `t_carinfo` VALUES ('3', '2016-05-23 10:36:41', '2016-05-23 10:36:41', '2', '5', null, null);
INSERT INTO `t_carinfo` VALUES ('4', '2016-05-23 10:37:15', '2016-05-23 10:37:15', '2', '3', null, null);

-- ----------------------------
-- Table structure for `t_car_user`
-- ----------------------------
DROP TABLE IF EXISTS `t_car_user`;
CREATE TABLE `t_car_user` (
  `phone` varchar(255) NOT NULL COMMENT '手机号',
  `passwd` varchar(255) DEFAULT NULL COMMENT '密码',
  `plate` varchar(255) DEFAULT NULL COMMENT '车牌号',
  `money` double DEFAULT NULL COMMENT '余额',
  PRIMARY KEY (`phone`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_car_user
-- ----------------------------
INSERT INTO `t_car_user` VALUES ('123', '202cb962ac59075b964b07152d234b70', '123', '0');
INSERT INTO `t_car_user` VALUES ('18888888888', 'c9f0f895fb98ab9159f51fd0297e236d', '湘A88888', '0');

-- ----------------------------
-- Table structure for `t_garageinfo`
-- ----------------------------
DROP TABLE IF EXISTS `t_garageinfo`;
CREATE TABLE `t_garageinfo` (
  `id` int(11) NOT NULL DEFAULT '0' COMMENT '编号',
  `name` varchar(255) DEFAULT NULL COMMENT '车库名',
  `nowstatus` int(11) DEFAULT NULL COMMENT '现在状态',
  `oldstatus` int(11) DEFAULT NULL COMMENT '上一状态',
  `command` varchar(255) DEFAULT NULL COMMENT '正在执行的命令',
  `sumcar` int(11) DEFAULT '-1' COMMENT '容量',
  `spendcar` int(11) DEFAULT '-1' COMMENT '已存车量',
  `map_rows` int(11) DEFAULT '-1' COMMENT '第几行',
  `map_cols` int(11) DEFAULT '-1' COMMENT '第几列',
  `rows` int(11) DEFAULT '-1' COMMENT '几行',
  `cols` int(11) DEFAULT '-1' COMMENT '几列',
  `speedrows` double(11,3) DEFAULT '-1.000' COMMENT '横向移动速度',
  `speedcols` double(11,3) DEFAULT '-1.000' COMMENT '纵向移动速度',
  `map_queue` text CHARACTER SET latin1 COMMENT '位置列表',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_garageinfo
-- ----------------------------
INSERT INTO `t_garageinfo` VALUES ('1', '1号车库', null, null, null, '-1', '-1', '-1', '-1', '5', '4', '1.000', '1.000', '1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 ');
INSERT INTO `t_garageinfo` VALUES ('2', '2', '6', null, null, '-1', '-1', '-1', '-1', '5', '4', '1.000', '1.000', '65537 2 65541 65539 6 9 7 10 13 4 11 14 17 8 15 18 12 19 16 20 ');
INSERT INTO `t_garageinfo` VALUES ('3', '3', null, null, null, '-1', '-1', '-1', '-1', '5', '4', '1.000', '1.000', '');
INSERT INTO `t_garageinfo` VALUES ('4', '4', null, null, null, '-1', '-1', '-1', '-1', '5', '4', '1.000', '1.000', '');

-- ----------------------------
-- Table structure for `t_history`
-- ----------------------------
DROP TABLE IF EXISTS `t_history`;
CREATE TABLE `t_history` (
  `time` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00' ON UPDATE CURRENT_TIMESTAMP COMMENT '当前时间',
  `plate` varchar(100) DEFAULT NULL COMMENT '车牌',
  `name` varchar(100) DEFAULT NULL COMMENT '车主姓名',
  `timestatus` int(11) DEFAULT NULL COMMENT '存车:1 取车:2 充值:3',
  `carbarnid` int(11) DEFAULT NULL COMMENT '车库编号',
  `carbarnname` varchar(255) DEFAULT NULL COMMENT '车库名',
  `num` int(11) DEFAULT NULL COMMENT '车位号',
  `rows` int(11) DEFAULT NULL COMMENT '第几行',
  `cols` int(11) DEFAULT NULL COMMENT '第几列',
  `money` double DEFAULT NULL COMMENT '充值/扣除费用',
  `balance` double unsigned zerofill DEFAULT NULL COMMENT '余额',
  KEY `plate` (`plate`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_history
-- ----------------------------
INSERT INTO `t_history` VALUES ('2016-06-12 16:15:41', '湘A88888', '小米', '1', '1', '1号车库', '1', '1', '1', null, null);

-- ----------------------------
-- Table structure for `t_idtoplatenumber`
-- ----------------------------
DROP TABLE IF EXISTS `t_idtoplatenumber`;
CREATE TABLE `t_idtoplatenumber` (
  `plate` varchar(255) NOT NULL COMMENT '车牌号',
  `idcard` int(11) DEFAULT NULL COMMENT '卡号',
  PRIMARY KEY (`plate`),
  KEY `plate_number` (`plate`) USING HASH
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_idtoplatenumber
-- ----------------------------

-- ----------------------------
-- Table structure for `t_map`
-- ----------------------------
DROP TABLE IF EXISTS `t_map`;
CREATE TABLE `t_map` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `x` int(11) NOT NULL COMMENT '坐标x',
  `y` int(11) NOT NULL COMMENT '坐标y',
  `type` int(11) NOT NULL COMMENT '类型',
  `type_id` int(11) NOT NULL COMMENT '类型id',
  `value` varchar(255) DEFAULT NULL COMMENT '注释',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=350 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_map
-- ----------------------------
INSERT INTO `t_map` VALUES ('317', '2', '1', '1', '1', '');
INSERT INTO `t_map` VALUES ('318', '2', '2', '4', '0', '');
INSERT INTO `t_map` VALUES ('319', '2', '3', '4', '0', '');
INSERT INTO `t_map` VALUES ('320', '3', '2', '4', '0', '');
INSERT INTO `t_map` VALUES ('321', '3', '1', '2', '1', '');
INSERT INTO `t_map` VALUES ('322', '2', '4', '4', '0', '');
INSERT INTO `t_map` VALUES ('323', '2', '5', '4', '0', '');
INSERT INTO `t_map` VALUES ('328', '3', '5', '4', '0', '');
INSERT INTO `t_map` VALUES ('329', '4', '5', '4', '0', '');
INSERT INTO `t_map` VALUES ('330', '4', '6', '4', '0', '');
INSERT INTO `t_map` VALUES ('331', '4', '7', '4', '0', '');
INSERT INTO `t_map` VALUES ('332', '4', '8', '4', '0', '');
INSERT INTO `t_map` VALUES ('345', '2', '6', '4', '0', '');
INSERT INTO `t_map` VALUES ('346', '2', '7', '3', '1', '');
INSERT INTO `t_map` VALUES ('347', '5', '5', '3', '2', null);
INSERT INTO `t_map` VALUES ('348', '4', '9', '3', '3', null);
INSERT INTO `t_map` VALUES ('349', '1', '5', '3', '4', null);

-- ----------------------------
-- Table structure for `t_reservation`
-- ----------------------------
DROP TABLE IF EXISTS `t_reservation`;
CREATE TABLE `t_reservation` (
  `plate` varchar(255) NOT NULL COMMENT '车牌号',
  `endtime` timestamp NULL DEFAULT NULL COMMENT '结束时间',
  `residuetime` int(11) DEFAULT NULL COMMENT '剩余时间',
  PRIMARY KEY (`plate`),
  KEY `plate_number` (`plate`) USING HASH
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_reservation
-- ----------------------------

-- ----------------------------
-- Table structure for `t_user`
-- ----------------------------
DROP TABLE IF EXISTS `t_user`;
CREATE TABLE `t_user` (
  `name` varchar(255) NOT NULL COMMENT '用户名',
  `password` varchar(255) NOT NULL COMMENT '密码',
  `type` int(11) DEFAULT NULL COMMENT '类型',
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_user
-- ----------------------------
