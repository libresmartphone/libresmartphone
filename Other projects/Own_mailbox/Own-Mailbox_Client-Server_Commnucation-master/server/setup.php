<html>
<head>

</head>
<body>
<h2> PLease enter the following inormations </h2>
<form  METHOD="POST" ACTION="setup-recup.php"> 
Mysql database user:<input type="text" placeholder="user" name="dbuser"></br>
Mysql database passphrase:<input type="text" placeholder="password" name="passphrase"></br>
Mysql database name:<input type="text" placeholder="omb" name="database"></br>
Prefix of the domain name handled by the proxy:<input type="text"  placeholder=".omb.one" name="domain_prefix"></br>
MySql table used by the tls proxy for its Association table:<input type="text"  placeholder="Association" name="table_tls_proxy"></br>
MySql database name used by postfix :<input type="text" placeholder="postfix" name="postfix_database"></br>
MySql table used by postfix for transportation:<input type="text" placeholder="transport"  name="table_postfix"></br>
Smtp tor transportation program:<input type="text" placeholder="smtptor"  name="postfix_tor_transportation_prefix"></br>
<input type="submit" name="search_bt" value="Continue">
</form>



</body>
</html>