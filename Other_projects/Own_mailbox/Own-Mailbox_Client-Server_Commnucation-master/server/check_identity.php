<?php
    include 'global_variables.php';
    $link =  mysql_connect('localhost', $db_user, $db_passphrase);
    if (!$link) {die("conection à la base de donnée impossible");}
   
   $db_selected = mysql_select_db($db_name,$link);
   

   $query=sprintf(" SELECT COUNT(ID) AS DB FROM Customers WHERE ID=".mysql_real_escape_string (strip_tags($_COOKIE['ID']))." AND passphrase='".mysql_real_escape_string (strip_tags($_COOKIE['passphrase']))."'");
   $reponse= mysql_query($query,$link);   
	
   if (!$reponse) {
	      $message  = 'Invalid query: ' . mysql_error() . "\n";
	      $message .= 'Whole query: ' . $query;
	      die($message);
	    }
	    
	    
    // On récupère les données
    if ($donnees = mysql_fetch_assoc($reponse))
	 {
	    if ($donnees['DB']!=1)
	      {
	      echo "<p>Invalid identifiaction cookie.</p>";
	      die();
	      }
	 }

?>