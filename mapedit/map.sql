
SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

--
-- 数据库: `test`
--

-- --------------------------------------------------------

--
-- 表的结构 `t_carinfo`
--

CREATE TABLE IF NOT EXISTS `t_carinfo` (
  `idcard` varchar(255) NOT NULL COMMENT '车卡号',
  `plate` varchar(255) DEFAULT NULL COMMENT '车牌号',
  `start` timestamp NULL DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP COMMENT '入库时间',
  `end` timestamp NULL DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`idcard`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- 表的结构 `t_carlocation`
--

CREATE TABLE IF NOT EXISTS `t_carlocation` (
  `idcard` varchar(255) NOT NULL COMMENT '车卡号',
  `plate` varchar(255) DEFAULT NULL COMMENT '车牌号',
  `carbarnid` int(11) DEFAULT NULL COMMENT '车库编号',
  `num` int(11) DEFAULT NULL,
  `rows` int(11) DEFAULT NULL COMMENT '第几行',
  `cols` int(11) DEFAULT NULL COMMENT '第几列',
  PRIMARY KEY (`idcard`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- 表的结构 `t_garageinfo`
--

CREATE TABLE IF NOT EXISTS `t_garageinfo` (
  `id` int(11) NOT NULL COMMENT '编号',
  `name` varchar(255) DEFAULT NULL COMMENT '车库名',
  `nowstatus` int(11) DEFAULT NULL COMMENT '现在状态',
  `oldstatus` int(11) DEFAULT NULL COMMENT '上一状态',
  `command` varchar(255) CHARACTER SET latin1 DEFAULT NULL COMMENT '正在执行的命令',
  `sumcar` int(11) DEFAULT NULL COMMENT '容量',
  `spendcar` int(11) DEFAULT NULL COMMENT '已存车量',
  `map_rows` int(11) DEFAULT '-1' COMMENT '第几行',
  `map_cols` int(11) DEFAULT '-1' COMMENT '第几列',
  `rows` int(11) DEFAULT NULL COMMENT '几行',
  `cols` int(11) DEFAULT NULL COMMENT '几列',
  `speedrows` double(11,3) DEFAULT NULL COMMENT '横向移动速度',
  `speedcols` double(11,3) DEFAULT NULL COMMENT '纵向移动速度',
  `map_queue` text CHARACTER SET latin1 COMMENT '位置列表',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- 转存表中的数据 `t_garageinfo`
--

INSERT INTO `t_garageinfo` (`id`, `name`, `nowstatus`, `oldstatus`, `command`, `sumcar`, `spendcar`, `map_rows`, `map_cols`, `rows`, `cols`, `speedrows`, `speedcols`, `map_queue`) VALUES
(1, 'a1', NULL, NULL, NULL, NULL, NULL, -1, -1, 2, 2, 1.000, 1.000, '131073 2 3 4 '),
(3, '1', NULL, NULL, NULL, NULL, NULL, -1, -1, 1, 1, 1.000, 1.000, '');

-- --------------------------------------------------------

--
-- 表的结构 `t_history`
--

CREATE TABLE IF NOT EXISTS `t_history` (
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

-- --------------------------------------------------------

--
-- 表的结构 `t_idtoplatenumber`
--

CREATE TABLE IF NOT EXISTS `t_idtoplatenumber` (
  `idcard` int(11) NOT NULL DEFAULT '0' COMMENT '车卡号',
  `plate` varchar(255) DEFAULT NULL COMMENT '车牌号',
  `username` varchar(255) DEFAULT NULL,
  `phone` varchar(255) DEFAULT NULL,
  `balance` double DEFAULT NULL COMMENT '余额',
  PRIMARY KEY (`idcard`),
  KEY `plate_number` (`plate`) USING HASH
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- 表的结构 `t_map`
--

CREATE TABLE IF NOT EXISTS `t_map` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `x` int(11) NOT NULL,
  `y` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `type_id` int(11) NOT NULL DEFAULT '0',
  `value` varchar(255) CHARACTER SET utf8mb4 NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=273 ;

--
-- 转存表中的数据 `t_map`
--

INSERT INTO `t_map` (`id`, `x`, `y`, `type`, `type_id`, `value`) VALUES
(197, 1, 2, 4, 0, ''),
(198, 1, 3, 4, 0, ''),
(200, 2, 3, 4, 0, ''),
(201, 3, 3, 4, 0, ''),
(204, 4, 3, 4, 0, ''),
(205, 3, 2, 4, 0, ''),
(206, 2, 1, 4, 0, ''),
(207, 4, 1, 4, 0, ''),
(208, 3, 1, 4, 0, ''),
(209, 5, 1, 4, 0, ''),
(210, 5, 2, 4, 0, ''),
(211, 5, 3, 4, 0, ''),
(213, 1, 5, 4, 0, ''),
(214, 1, 6, 4, 0, ''),
(215, 1, 7, 4, 0, ''),
(216, 2, 7, 4, 0, ''),
(217, 3, 7, 4, 0, ''),
(218, 4, 7, 4, 0, ''),
(219, 5, 7, 4, 0, ''),
(220, 5, 6, 4, 0, ''),
(221, 5, 5, 4, 0, ''),
(222, 4, 5, 4, 0, ''),
(223, 3, 5, 4, 0, ''),
(224, 2, 5, 4, 0, ''),
(225, 3, 6, 4, 0, ''),
(227, 1, 9, 4, 0, ''),
(228, 1, 10, 4, 0, ''),
(229, 1, 11, 4, 0, ''),
(230, 2, 9, 4, 0, ''),
(231, 3, 9, 4, 0, ''),
(232, 3, 10, 4, 0, ''),
(234, 3, 11, 4, 0, ''),
(235, 4, 11, 4, 0, ''),
(236, 5, 11, 4, 0, ''),
(237, 5, 10, 4, 0, ''),
(238, 5, 9, 4, 0, ''),
(240, 1, 13, 4, 0, ''),
(241, 1, 14, 4, 0, ''),
(242, 1, 15, 4, 0, ''),
(243, 2, 15, 4, 0, ''),
(244, 3, 15, 4, 0, ''),
(245, 3, 14, 4, 0, ''),
(246, 3, 13, 4, 0, ''),
(247, 4, 13, 4, 0, ''),
(248, 5, 13, 4, 0, ''),
(249, 5, 14, 4, 0, ''),
(250, 5, 15, 4, 0, ''),
(252, 1, 17, 4, 0, ''),
(253, 1, 18, 4, 0, ''),
(254, 2, 17, 4, 0, ''),
(256, 1, 19, 4, 0, ''),
(257, 3, 17, 4, 0, ''),
(258, 4, 17, 4, 0, ''),
(259, 5, 17, 4, 0, ''),
(260, 5, 18, 4, 0, ''),
(261, 2, 19, 4, 0, ''),
(262, 3, 19, 4, 0, ''),
(263, 4, 19, 4, 0, ''),
(264, 5, 19, 4, 0, ''),
(268, 1, 1, 4, 0, ''),
(270, 7, 2, 3, 1, ''),
(271, 7, 3, 2, 1, '出口1'),
(272, 7, 1, 1, 1, '入口1');

-- --------------------------------------------------------

--
-- 表的结构 `t_reservation`
--

CREATE TABLE IF NOT EXISTS `t_reservation` (
  `idcard` int(11) NOT NULL DEFAULT '0' COMMENT '车卡号',
  `plate` varchar(255) DEFAULT NULL COMMENT '车牌号',
  PRIMARY KEY (`idcard`),
  KEY `plate_number` (`plate`) USING HASH
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- 表的结构 `t_user`
--

CREATE TABLE IF NOT EXISTS `t_user` (
  `name` varchar(255) DEFAULT NULL,
  `password` varchar(255) DEFAULT NULL,
  `type` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

