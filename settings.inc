<?php
// $Id$

function events_settings_form($form,&$form_state)
{

  $form['extensions']['image'] = array(
    '#type' => 'textfield',
    '#title' => t('Allowed image file extensions'),
    '#description' => t('A comma separated list WITHOUT SPACE of source file extensions that are permitted to be uploaded on the server'),
    '#size' => 50,
    '#maxlength' => 255,
    '#required' => TRUE,
    '#default_value' => variable_get('events_image_extensions', ''),
  );
  $form['extensions']['poster'] = array(
    '#type' => 'textfield',
    '#title' => t('Allowed poster file extensions'),
    '#description' => t('A comma separated list WITHOUT SPACE of source file extensions that are permitted to be uploaded on the server'),
    '#size' => 50,
    '#maxlength' => 255,
    '#required' => TRUE,
    '#default_value' => variable_get('events_poster_extensions', ''),
  );
  $form['maxuploadsize'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum file upload size(MB): '),
    '#description' => t('Maximum allowed size of upload file in MB'),
    '#maxlength' => 5,
    '#required' => TRUE,
    '#default_value' => variable_get('max_upload_size', ''),
  );

  $form['email_id_bcc'] = array(
    '#type' => 'textfield',
    '#title' => t('Email of admin to be notified after addition/change in any workshop details'),
    '#description' => t('An email will be sent to this id if any user changes/adds any workshop detail along with the email sent to that user'),
    '#required' => TRUE,
    '#default_value' => variable_get('email_bcc', ''),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit')
  );
  return $form;
}

function events_settings_form_validate($form, &$form_state)
{
  return;
}

function events_settings_form_submit($form, &$form_state)
{

  variable_set('events_image_extensions', $form_state['values']['image']);
  variable_set('events_poster_extensions', $form_state['values']['poster']);
  variable_set('max_upload_size', $form_state['values']['maxuploadsize']);
  variable_set('email_bcc', $form_state['values']['email_id_bcc']);
  drupal_set_message(t('Settings updated'), 'status');
}
