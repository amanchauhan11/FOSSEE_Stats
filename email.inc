<?php

function fossee_stats_mail($key, &$message, $params)
{
	global $user;
	switch($key)
	{
		case 'edit_mail': 
		  $message['to'] = $user->mail;
		  $message['bcc'] = 'site_admin_mail_goes_here';
	      $message['subject'] = t('Changes made in workshop details');
	      $message['body'][] = t('Hello '.$user->name.','); 
	      $message['body'][] = t('We noticed that you made some changes in the event "'.$params['workhsop_name'].'" at fossee.in. If you didn\'t make these changes, report to the site admin.');
	      break;
	}
}