/*
Navicat MySQL Data Transfer

Source Server         : 127.0.0.1
Source Server Version : 50612
Source Host           : localhost:3306
Source Database       : car

Target Server Type    : MYSQL
Target Server Version : 50612
File Encoding         : 65001

Date: 2015-12-06 10:54:53
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `t_carinfo`
-- ----------------------------
DROP TABLE IF EXISTS `t_carinfo`;
CREATE TABLE `t_carinfo` (
  `idcard` varchar(255) NOT NULL COMMENT '车卡号',
  `plate` varchar(255) DEFAULT NULL COMMENT '车牌号',
  `name` varchar(255) DEFAULT NULL COMMENT '车主姓名',
  `carbarnid` int(11) DEFAULT NULL COMMENT '车库编号',
  `carbarnname` varchar(255) DEFAULT NULL COMMENT '车库名',
  `rows` int(11) DEFAULT NULL COMMENT '第几行',
  `cols` int(11) DEFAULT NULL COMMENT '第几列',
  `start` timestamp NULL DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP COMMENT '入库时间',
  PRIMARY KEY (`idcard`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of t_carinfo
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
  `plate` char(30) NOT NULL COMMENT '车牌号',
  `balance` double DEFAULT NULL COMMENT '余额',
  PRIMARY KEY (`idcard`),
  KEY `plate_number` (`plate`) USING HASH
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of t_idtoplatenumber
-- ----------------------------

-- ----------------------------
-- Table structure for `t_mapinfo`
-- ----------------------------
DROP TABLE IF EXISTS `t_mapinfo`;
CREATE TABLE `t_mapinfo` (
  `rows` int(11) NOT NULL DEFAULT '0',
  `cols` int(11) DEFAULT NULL,
  PRIMARY KEY (`rows`)
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
