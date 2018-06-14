<?php

function fossee_stats_mail($key, &$message, $params)
{
	if(variable_get('email_bcc'))
		$message['headers']['Bcc'] = variable_get('email_bcc');
	global $user;
	switch($key)
	{
		case 'edit_mail': 
	      $message['subject'] = t('Changes made in workshop details');
	      $message['body'][] = t('Hello '.$user->name.','); 
	      $message['body'][] = t('We noticed that you made some changes in the event "'.$params['workshop_name'].'" at fossee.in. If you didn\'t make these changes, please report this to the site admin.');
	      break;
	    case 'upload_csv_mail':
	      $message['subject'] = t('Changes made in workshop details');
	      $message['body'][] = t('Hello '.$user->name.','); 
	      $message['body'][] = t('We noticed that you added some events through csv file "'.$params['csv_filename'].'" at fossee.in. If you didn\'t make these changes, please report this to the site admin.');
	      break;
	}
}