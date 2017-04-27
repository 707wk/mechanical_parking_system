<?php
/*************************************
 *CREATED :2016/4/20
 *TEXT    :立体车库管理后台
 *EMAIL   :dksx@qq.com
 *************************************/
 require_once "main.php";
 needLogin();
?>
<!DOCTYPE html >
<html >
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>立体车库管理后台</title>
<script>
</script>
</head>
<frameset rows="51,*" cols="*" frameborder="no" border="0" framespacing="0" >
  <frame src="top.php" name="topFrame" scrolling="No" noresize="noresize" id="topFrame" />
  <frameset name="BottomArea" cols="110,*" frameborder="no" border="0" framespacing="0">
    <frame src="left.php" name="leftFrame" scrolling="No" noresize="noresize" id="leftFrame" />
    <frame src="state.php" name="mainFrame" id="mainFrame" />
  </frameset>
</frameset>
</html>