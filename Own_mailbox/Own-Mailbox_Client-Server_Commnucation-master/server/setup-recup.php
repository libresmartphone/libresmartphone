<html>
<head>

</head>
<body>
Please copy the following content in the file <b>global_variables.php</b> :</br></br>

<?php
echo "<code>&lt;?php </br>\n";
echo "\$db_user=\"".$_POST["dbuser"]."\";</br>";
echo "\$db_passphrase=\"".$_POST["passphrase"]."\";</br>";
echo "\$db_name=\"".$_POST["database"]."\";</br>";
echo "\$domain_post_fix=\"".$_POST["domain_prefix"]."\";</br>";
echo "\$table_tls_proxy=\"".$_POST["table_tls_proxy"]."\";</br>";
echo "\$data_base_postfix=\"".$_POST["postfix_database"]."\";</br>";
echo "\$table_postfix=\"".$_POST["table_postfix"]."\";</br>";
echo "\$postfix_tor_transportation_prefix=\"".$_POST["postfix_tor_transportation_prefix"]."\";</br>";
echo "?></br>\n";
echo "</code>\n";
?>


</body>
</html>