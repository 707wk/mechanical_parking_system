/*
Navicat MySQL Data Transfer

Source Server         : 127.0.0.1
Source Server Version : 50612
Source Host           : localhost:3306
Source Database       : car

Target Server Type    : MYSQL
Target Server Version : 50612
File Encoding         : 65001

Date: 2015-12-05 20:00:45
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `t_carinfo`
-- ----------------------------
DROP TABLE IF EXISTS `t_carinfo`;
CREATE TABLE `t_carinfo` (
  `id` varchar(100) NOT NULL,
  `plate` varchar(100) DEFAULT NULL,
  `name` varchar(100) DEFAULT NULL,
  `number` int(11) DEFAULT NULL,
  `rows` int(11) DEFAULT NULL,
  `cols` int(11) DEFAULT NULL,
  `start` timestamp NULL DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='id           //卡号\r\nmac        //存储车库mac\r\nindex      //第几个\r\nrows       //第几行\r\ncols        //第几列\r\n';

-- ----------------------------
-- Records of t_carinfo
-- ----------------------------

-- ----------------------------
-- Table structure for `t_garageinfo`
-- ----------------------------
DROP TABLE IF EXISTS `t_garageinfo`;
CREATE TABLE `t_garageinfo` (
  `name` varchar(100) NOT NULL,
  `map_rows` int(11) DEFAULT '-1',
  `map_cols` int(11) DEFAULT '-1',
  `rows` int(11) DEFAULT NULL,
  `cols` int(11) DEFAULT NULL,
  `speedrows` double(11,3) DEFAULT NULL,
  `speedcols` double(11,3) DEFAULT NULL,
  `sumcar` int(11) DEFAULT NULL,
  `spendcar` int(11) DEFAULT NULL,
  `map_queue` text,
  `state` int(11) DEFAULT '0',
  `compotr` int(11) DEFAULT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='mac             //存储车库mac\r\nmap_rows    //地图第几行\r\nmap_cols     //地图第几列\r\nrows            //共几行\r\ncols             //共几列\r\nspeedrows   //横轴移动速度\r\nspeedcols    //纵轴移动速度\r\nsumcar        //总存车量\r\nspendcar     //已存车量\r\nmap_queue  //存放位置列表\r\nstate            //状态\r\ncompotr      //端口号\r\n';

-- ----------------------------
-- Records of t_garageinfo
-- ----------------------------

-- ----------------------------
-- Table structure for `t_history`
-- ----------------------------
DROP TABLE IF EXISTS `t_history`;
CREATE TABLE `t_history` (
  `time` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00' ON UPDATE CURRENT_TIMESTAMP,
  `plate` varchar(100) DEFAULT NULL,
  `id` varchar(100) DEFAULT NULL,
  `name` varchar(100) DEFAULT NULL,
  `timestatus` int(11) DEFAULT NULL,
  `balancestatus` double DEFAULT NULL,
  `money` double DEFAULT NULL,
  PRIMARY KEY (`time`),
  KEY `plate` (`plate`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='time               //当前时间\r\nplate_number //车牌\r\nid                  //卡号\r\nmac               //存储车库mac\r\ntimestatus      //存车:1 取车:2\r\nbalancestatus //充值:1 扣费:2\r\nmoney           //充值/扣除费用\r\nbalance         //充值/扣除之后余额\r\n';

-- ----------------------------
-- Records of t_history
-- ----------------------------

-- ----------------------------
-- Table structure for `t_idtoplatenumber`
-- ----------------------------
DROP TABLE IF EXISTS `t_idtoplatenumber`;
CREATE TABLE `t_idtoplatenumber` (
  `id` int(11) NOT NULL DEFAULT '0',
  `plate` char(30) NOT NULL,
  `balance` double DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `plate_number` (`plate`) USING HASH
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='id                  //卡号\r\nplate_number //车牌\r\nbalance         //余额\r\nstart              //停车时间\r\nend               //取车时间\r\n';

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
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='rows  //地图行数\r\ncols   //地图列数\r\n';

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
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='rows    //第几行\r\ncols     //第几列\r\nobject  //对象是什么\r\n';

-- ----------------------------
-- Records of t_maplocation
-- ----------------------------
