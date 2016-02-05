<?php

$torhidenservice= $_GET["service"];

include 'check_identity.php';


include 'global_variables.php';

//*************************************************
//Check that the customer has no hiden service yet.
//*************************************************

$link =  mysql_connect('localhost', $db_user, $db_passphrase);
  if (!$link) {die("conection à la base de donnée impossible");}
  
  $db_selected = mysql_select_db($db_name,$link);
  

  $query=sprintf(" SELECT LENGTH(tor_hidden) FROM Customers WHERE ID=".mysql_real_escape_string (strip_tags($_COOKIE['ID'])));
  $reponse= mysql_query($query,$link);   
      
  if (!$reponse) {
	    $message  = 'Invalid query: ' . mysql_error() . "\n";
	    $message .= 'Whole query: ' . $query;
	    die($message);
	  }
	  
 // On affiche chaque entrée une à une
	
 if ($donnees = mysql_fetch_assoc($reponse))
	{
	  if ($donnees['LENGTH(tor_hidden)']>0)
	    {
	    echo "This account allready has a tor hidden service.\n";
	    die();
	    }
	}	        
	
//*********************************************
//Get corresponding domain_omb
//*********************************************

$domain="";

  $query=sprintf(" SELECT domain_omb FROM Customers WHERE ID=".mysql_real_escape_string (strip_tags($_COOKIE['ID'])));
  $reponse= mysql_query($query,$link);   
      
  if (!$reponse) {
	    $message  = 'Invalid query: ' . mysql_error() . "\n";
	    $message .= 'Whole query: ' . $query;
	    die($message);
	  }
	  
 // On affiche chaque entrée une à une
	
 if ($donnees = mysql_fetch_assoc($reponse))
	{
	$domain=$donnees['domain_omb'];
	}	

	
echo "Setting hiden service:".$torhidenservice."\n";	
//*********************************************
//Update entry for TLS proxy
//*********************************************
include 'tls_proxy_database.php';
tls_proxy_update_domain($domain,$torhidenservice);

//*********************************************
//Update entry for SMTP proxy
//*********************************************
 include 'postfix_database.php';
 
postfix_update_domain($domain,$torhidenservice);

//*********************************************
//Add tor service in 
//*********************************************

$link =  mysql_connect('localhost', $db_user, $db_passphrase);
  if (!$link) {die("conection à la base de donnée impossible");}
  
  $db_selected = mysql_select_db($db_name,$link);
  
  $query=sprintf(" UPDATE Customers set tor_hidden =\"".$torhidenservice."\" WHERE ID=".mysql_real_escape_string (strip_tags($_COOKIE['ID'])));
  $reponse= mysql_query($query,$link);   
      
  if (!$reponse) {
	    $message  = 'Invalid query: ' . mysql_error() . "\n";
	    $message .= 'Whole query: ' . $query;
	    die($message);
	  }
?>