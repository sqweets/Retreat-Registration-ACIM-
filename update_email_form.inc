<?php

/**
 * This file contains the form for sending an update message to all.
 */

require_once("retreatform_defines.inc");
require_once("retreatform_mail.inc");

function form_update_email($form, &$form_state) {

  $form['info'] = array(
      '#markup' => t('Message to be sent to all registrants'),
  );

  $form['subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#size' => 60,
    '#maxlength' => 60,
    '#required' => TRUE,
  );
  $form['from'] = array(
    '#type' => 'textfield',
    '#title' => t('Your Name and/or Title'),
    '#size' => 60,
    '#maxlength' => 60,
    '#required' => TRUE,
  );
  $form['message'] = array(
    '#type' => 'textarea',
    '#title' => t('Message'),
  );

  $form['send_emails'] = array(
    '#type' => 'submit',
    '#value' => t('SEND message'),
    '#submit' => array('form_update_email_submit'),
  );

  return $form;
}

/**
 * The submit handler.
 */
function form_update_email_submit($form, &$form_state) {
  $msg_values = array('from' => $form_state['values']['from'],
                  'message' => $form_state['values']['message'],
                  'subject' => $form_state['values']['subject'],
                  );

  // Get the emails
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'retreat_registration')
    ->propertyCondition('status', 1)
    ->fieldCondition('field_cancelled', 'value', 0, '=')
    ->fieldCondition('field_year_of_retreat', 'value', YEAR, '=');
  
  $all_registrations = $query->execute();
  if (isset($all_registrations['node'])) {
    $email_nids = array_keys($all_registrations['node']);
    $emails = entity_load('node', $email_nids);
  }
  
  if (!(empty($emails))) {
    foreach($emails as $key => $value) {
      $email_address = field_get_items('node', $value, 'field_email_address');
      
      $msg_values['email'] = $email_address[0]['value'];
      
      // Send email
      email_update_send($msg_values);
   }
  }

}




