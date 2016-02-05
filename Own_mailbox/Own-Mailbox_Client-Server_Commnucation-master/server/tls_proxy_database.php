<?php

function tls_proxy_update_domain($domain,$torhidenservice)
{
    //check if the torhidenservice or the domain is empty
    if ($torhidenservice=="" or $domain=="")
    {
      echo "domain or tor hidden service is empty\n";
      return;
    }
    
    $allready_exists=0;
    //check if domain allready exists in the table.
    include 'global_variables.php';
    
    $link =  mysql_connect('localhost', $db_user, $db_passphrase);
    if (!$link) {echo "tls_proxy: conection à la base de donnée impossible\n"; return;}
  
    $db_selected = mysql_select_db($db_name,$link);
    
    $query=sprintf(" SELECT COUNT(ID) AS NB FROM ".mysql_real_escape_string (strip_tags($table_tls_proxy))." WHERE hostname= '".mysql_real_escape_string (strip_tags($domain.$domain_post_fix))."'");
    $reponse= mysql_query($query,$link);   
      
      if (!$reponse) {
	    $message  = 'Invalid query: ' . mysql_error() . "\n";
	    $message .= 'Whole query: ' . $query;
	    die($message);
	  }
	  
      // On affiche chaque entrée une à une
	
    if ($donnees = mysql_fetch_assoc($reponse))
	{
	if($donnees['NB']>0)
	  $allready_exists=1;
	}
    
    //On réalise une opération différente en fonction
    //de si le domaine existe 
    if($allready_exists)
    {
    
    echo "Error: tls_proxy_database update not yet supported!\n";
    
    }
    else
    {


    $query=sprintf(" INSERT  INTO ".mysql_real_escape_string (strip_tags($table_tls_proxy))."(hostname,torservice) VALUES('".mysql_real_escape_string (strip_tags($domain.$domain_post_fix))."','".mysql_real_escape_string (strip_tags($torhidenservice))."')");
    $reponse= mysql_query($query,$link);   
      
    if (!$reponse) {
	    $message  = 'Invalid query: ' . mysql_error() . "\n";
	    $message .= 'Whole query: ' . $query. "\n";
	    echo $message;
	    return;
	  }
    
    }
    
}




?>