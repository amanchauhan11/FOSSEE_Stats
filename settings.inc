<?php
// $Id$

function events_settings_form($form_state)
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
   drupal_set_message(t('Settings updated'), 'status');
}

