
-- 表的结构 `map`

CREATE TABLE IF NOT EXISTS `map` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `x` int(11) NOT NULL,
  `y` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `value` varchar(50) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=29 ;
--
-- 转存表中的数据 `map`
--
INSERT INTO `map` (`id`, `x`, `y`, `type`, `value`) VALUES
(3, 3, 2, 3, '1'),
(4, 3, 3, 3, '2'),
(6, 5, 5, 4, ''),
(7, 5, 6, 4, ''),
(8, 5, 7, 4, ''),
(9, 5, 8, 4, ''),
(10, 4, 5, 4, ''),
(16, 6, 6, 4, ''),
(17, 7, 6, 4, ''),
(18, 5, 9, 4, ''),
(19, 4, 6, 3, '3'),
(20, 4, 4, 4, ''),
(21, 4, 3, 4, ''),
(22, 4, 2, 4, ''),
(23, 4, 1, 4, ''),
(24, 4, 0, 3, '4'),
(25, 5, 4, 3, '5'),
(26, 5, 10, 3, '6'),
(27, 5, 1, 1, 'in1'),
(28, 6, 7, 2, 'out2');
