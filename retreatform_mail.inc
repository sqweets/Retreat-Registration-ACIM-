<?php

/**
 *
 * This file has the mail functions for the
 * RetreatForm module
 * 
 */

require_once("retreatform_defines.inc");
 
/**
 * Implement hook_mail().
 */
function retreatform_mail($key, &$message, $params) {
  $options = array(
    'langcode' => $message['language']->language,
  );

  switch ($key) {
    // Send a payment received email
    case 'payment_received':
      $message['subject'] = t('@subject - Payment Received', array('@subject' => RETREAT_SUBJECT), $options);
      $message['body'][] = t('@name, thank you for sending in your payment for "@title".  Your registration is now complete.  Details on the retreat can be found on the St. Louis ACIM website.', array('@name' => $params['first'], '@title' => RETREAT_TITLE), $options);
      $message['body'][] = t("\n&nbsp;\nQuestions should be directed to @coord_name, Retreat Coordinator, @coord_number or @coord_email.", array('@coord_name' => RETREAT_COORD, '@coord_number' => RETREAT_COORD_PHONE, '@coord_email' => RETREAT_COORD_EMAIL));
      $message['body'][] = t("\n&nbsp;\n<strong>If there is a change in your plans and you are not able to attend the retreat, a refund is provided up to 30 days prior to the retreat, minus an administrative processing fee.</strong>");
      break;
    // Send an update to all registrants
    case 'update':
      $message['subject'] = check_plain($params['subject']);
      $message['body'][] = t("From: @name\n&nbsp;\n@message", array('@name' => $params['from'], '@message' => $params['message']));
      break;
    // Send a message to an individual
    case 'individual':
      $message['subject'] = check_plain($params['subject']);
      $message['body'][] = t("From: @name\n&nbsp;\n@message", array('@name' => $params['from'], '@message' => $params['message']));
      break;
    // Send a confirmation message from the registration.
    case 'registration_message':
      // Check if additional text is needed
      if ($params[2]['first_retreat'] == 'No') {
        $returning = '  It is great to have you with us again at Mercy Center.';
      } else {
        $returning = NULL;
      }
      $message['subject'] = t('@subject Registration', array('@subject' => RETREAT_SUBJECT), $options);
      // Note that the message body is an array, not a string.
      $message['body'][] = t("@name, thank you for your registration.@returning  You will receive updates and reminders as the retreat gets closer.  If you have any questions, please contact @coord_name, Retreat Coordinator, @coord_number or @coord_email.", array('@name' => $params[1]['first'], '@returning' => $returning, '@coord_name' => RETREAT_COORD, '@coord_number' => RETREAT_COORD_PHONE, '@coord_email' => RETREAT_COORD_EMAIL), $options);
      // Check if additional text should be for scholarship or not
      if ($params[2]['form_of_payment'] == 'Scholarship') {
        $message['body'][] = t("\n&nbsp;\n<p><strong>Your registration is not finalized until your scholarship application is approved. The event coordinator will notify you once your application has been reviewed.<br>
          If there is a change in your plans and you are not able to attend the event, any applicable payment will be refunded up to 30 days prior to the event, minus an administrative processing fee.</strong></p>");
      } else {
        $message['body'][] = t("\n&nbsp;\n<strong>If there is a change in your plans and you are not able to attend the event, a refund is provided up to 30 days prior to the event, minus an administrative processing fee.</strong>");
      }
      break;
    // Send form email for mailed payments
    case 'form':
      $message['subject'] = t('@subject Form', array('@subject' => RETREAT_SUBJECT), $options);
      // Note that the message body is an array, not a string.
      $message['body'][] = t("@name, your registration info is below.  Please print and mail with payment to:\n&nbsp;\n@coord_name, Retreat Coordinator\n@line_1\n@line_2\n&nbsp;\n", array('@name' => $params[1]['first'], '@coord_name' => RETREAT_COORD, '@line_1' => RETREAT_COORD_ADDRESS_LINE1, '@line_2' => RETREAT_COORD_ADDRESS_LINE2), $options);

      $phone1 = substr($params[1]['phone'], 0, 3);
      $phone2 = substr($params[1]['phone'], 3, 3);
      $phone3 = substr($params[1]['phone'], 6, 4);
      
      if ($params[1]['address2'] == '') {
        $address2 = NULL;
      } else {
        $address2 = t("\n@line2", array('@line2' => $params[1]['address2']));
      }
      if ($params[1]['zip_code'] != '') {
        $message['body'][] = t("@first @last\n@address@address2\n@city, @state @zip\n@country\n(@phone1) @phone2-@phone3\n@email",
                                array('@first' => $params[1]['first'],
                                      '@last' => $params[1]['last'],
                                      '@address' => $params[1]['address'],
                                      '@address2' => $address2,
                                      '@city' => $params[1]['city'],
                                      '@state' => $params[1]['state'],
                                      '@zip' => $params[1]['zip_code'],
                                      '@country' => $params[1]['country'],
                                      '@phone1' => $phone1,
                                      '@phone2' => $phone2,
                                      '@phone3' => $phone3,
                                      '@email' => $params[1]['email'],
                                      ),
                                      $options);
      } elseif (strtoupper($params[1]['state']) != 'NONE') {
        $message['body'][] = t("@first @last\n@address@address2\n@city @state  @postal_code\n@country\n(@phone1) @phone2-@phone3\n@email",
                                array('@first' => $params[1]['first'],
                                      '@last' => $params[1]['last'],
                                      '@address' => $params[1]['address'],
                                      '@address2' => $address2,
                                      '@city' => $params[1]['city'],
                                      '@state' => $params[1]['state'],
                                      '@postal_code' => $params[1]['postal_code'],
                                      '@country' => $params[1]['country'],
                                      '@phone1' => $phone1,
                                      '@phone2' => $phone2,
                                      '@phone3' => $phone3,
                                      '@email' => $params[1]['email'],
                                      ),
                                      $options);        
      } elseif (strtoupper($params[1]['state']) == 'NONE') {
        $message['body'][] = t("@first @last\n@address@address2\n@postal_code @city\n@country\n(@phone1) @phone2-@phone3\n@email",
                                array('@first' => $params[1]['first'],
                                      '@last' => $params[1]['last'],
                                      '@address' => $params[1]['address'],
                                      '@address2' => $address2,
                                      '@city' => $params[1]['city'],
                                      '@postal_code' => $params[1]['postal_code'],
                                      '@country' => $params[1]['country'],
                                      '@phone1' => $phone1,
                                      '@phone2' => $phone2,
                                      '@phone3' => $phone3,
                                      '@email' => $params[1]['email'],
                                      ),
                                      $options);        
      }
      if ($params[2]['option'] != OPTION_3) {
        $roommate = NULL;
      } else if ($params[2]['roommate'] == 'not matched') {
        $roommate = t("\nRoommate: My roommate has not registered yet");
      } else {
        $roommate = t("\nRoommate: @roommate", array('@roommate' => $params[2]['roommate']));
      }
      if ($params[2]['meal_details'] == '') {
        $meal_details = NULL;
      } else {
        $meal_details = t("\nMeal Details: @meal_details", array('@meal_details' => $params[2]['meal_details']));
      }
      if ($params[2]['needs_info'] == '') {
        $needs_info = NULL;
      } else {
        $needs_info = t("\nSpecial Needs Details: @needs_info", array('@needs_info' => $params[2]['needs_info']));
      }
      if (SCHOLARSHIP_OPTION == 'Yes') {
        $message['body'][] = t("Option: @option@roommate\nMeal Needs: @meal@meal_details\nSpecial Needs: @special_needs@needs_info\nDonation: $@donation",
                                array('@option' => $params[2]['option'] . STR_FOR_COST . room_costs($params[2]['option']),
                                      '@roommate' => $roommate,
                                      '@meal' => $params[2]['meal'],
                                      '@meal_details' => $meal_details,
                                      '@special_needs' => $params[2]['special_needs'],
                                      '@needs_info' => $needs_info,
                                      '@donation' => $params[2]['donation'],
                                      ),
                                      $options);
      } else {
        $message['body'][] = t("Option: @option@roommate\nMeal Needs: @meal@meal_details\nSpecial Needs: @special_needs@needs_info",
                                array('@option' => $params[2]['option'] . STR_FOR_COST . room_costs($params[2]['option']),
                                      '@roommate' => $roommate,
                                      '@meal' => $params[2]['meal'],
                                      '@meal_details' => $meal_details,
                                      '@special_needs' => $params[2]['special_needs'],
                                      '@needs_info' => $needs_info,
                                      ),
                                      $options);
      }
                                
      if (SCHOLARSHIP_OPTION == 'Yes') {                                
        $total = room_costs($params[2]['option']) + intval($params[2]['donation']);
      } else {
        $total = room_costs($params[2]['option']);
      }
      
      $message['body'][] = t("\n&nbsp;\n<strong>Your total is: $@total</strong>", array('@total' => $total), $options);
      $message['body'][] = t("\n<strong>Please make your check payable to \"ACIM St. Louis\"</strong>", array('@total' => $total), $options);
      $message['body'][] = t("\n<strong>Registration is considered \"incomplete\" until your check is received and payment is made in full.</strong>");
      $message['body'][] = t("\n<strong>If there is a change in your plans and you are not able to attend the retreat, a refund is provided up to 30 days prior to the retreat, minus an administrative processing fee.</strong>");
      break;
  }
}

/**
 * Sends an registration confirmation e-mail.
 *
 * @param $form_values
 *   An array of values from the contact form fields that were submitted.
 *   There are just two relevant items: ['email'] and ['message'].
 */
function email_confirm_send($form_values) {
  // All system mails need to specify the module and template key (mirrored from
  // hook_mail()) that the message they want to send comes from.
  $module = 'retreatform';
  $key = 'registration_message';

  // Specify 'to' and 'from' addresses.
  $to = $form_values[1]['email'];
  $from = variable_get('site_mail', 'admin@acimstlouis.org');
    
  // "params" loads in additional context for email content completion in
  // hook_mail(). In this case, we want to pass in the values the user entered
  // into the form, which include the message body in $form_values['message'].
  $params = $form_values;

  $language = language_default();

  $send = TRUE;

  $result = drupal_mail($module, $key, $to, $language, $params, $from, $send);
  if ($result['result'] == TRUE) {
    drupal_set_message(t('Your confirmation message has been sent.'));
  }
  else {
    drupal_set_message(t('There was a problem sending your confirmation message and it was not sent.'), 'error');
  }
  
  return $result;
}

/**
 * Sends a form e-mail.
 *
 * @param $form_values
 *   An array of values from the contact form fields that were submitted.
 *   There are just two relevant items: ['email'] and ['message'].
 */
function email_form_send($form_values) {
  // All system mails need to specify the module and template key (mirrored from
  // hook_mail()) that the message they want to send comes from.
  $module = 'retreatform';
  $key = 'form';

  // Specify 'to' and 'from' addresses.
  $to = $form_values[1]['email'];
  $from = variable_get('site_mail', 'admin@acimstlouis.org');
    
  // "params" loads in additional context for email content completion in
  // hook_mail(). In this case, we want to pass in the values the user entered
  // into the form, which include the message body in $form_values['message'].
  $params = $form_values;

  $language = language_default();

  $send = TRUE;

  $result = drupal_mail($module, $key, $to, $language, $params, $from, $send);
  if ($result['result'] == TRUE) {
    drupal_set_message(t('Your form message has been sent.'));
  }
  else {
    drupal_set_message(t('There was a problem sending your form message and it was not sent.'), 'error');
  }
  
  return $result;
}

/**
 * Sends an update e-mail.
 *
 * @param $form_values
 *   An array of values from the contact form fields that were submitted.
 *   There are just two relevant items: ['email'] and ['message'].
 */
function email_update_send($values) {
  // All system mails need to specify the module and template key (mirrored from
  // hook_mail()) that the message they want to send comes from.
  $module = 'retreatform';
  $key = 'update';

  // Specify 'to' and 'from' addresses.
  $to = $values['email'];
  $from = variable_get('site_mail', 'admin@acimstlouis.org');
    
  // "params" loads in additional context for email content completion in
  // hook_mail(). In this case, we want to pass in the values the user entered
  // into the form, which include the message body in $form_values['message'].
  $params = $values;

  $language = language_default();

  $send = TRUE;

  $result = drupal_mail($module, $key, $to, $language, $params, $from, $send);
  if ($result['result'] == TRUE) {
    drupal_set_message(t('Your update message has been sent.'));
  }
  else {
    drupal_set_message(t('There was a problem sending your update message and it was not sent.'), 'error');
  }
  
  return $result;
}

/**
 * Sends an individual e-mail.
 *
 * @param $form_values
 *   An array of values from the contact form fields that were submitted.
 *   There are just two relevant items: ['email'] and ['message'].
 */
function email_individual_send($values) {
  // All system mails need to specify the module and template key (mirrored from
  // hook_mail()) that the message they want to send comes from.
  $module = 'retreatform';
  $key = 'individual';

  // Specify 'to' and 'from' addresses.
  $to = $values['email'];
  $from = variable_get('site_mail', 'admin@acimstlouis.org');
    
  // "params" loads in additional context for email content completion in
  // hook_mail(). In this case, we want to pass in the values the user entered
  // into the form, which include the message body in $form_values['message'].
  $params = $values;

  $language = language_default();

  $send = TRUE;

  $result = drupal_mail($module, $key, $to, $language, $params, $from, $send);
  if ($result['result'] == TRUE) {
    drupal_set_message(t('Your individual message has been sent.'));
    
    // Create the log entry
    // Create a node object
    $node = new stdClass();
    $node->type = 'email_log_entry';
    node_object_prepare($node);
  
    // Save title
    $node->title    = $values['first'] . ' ' . $values['last'];
    $node->language = LANGUAGE_NONE;

    // Save retreat year
    $node->field_year_of_retreat[$node->language][0]['value']    = YEAR;
    // Save form values
    $node->field_key[$node->language][0]['value']       = $key;
    $node->field_sent_to[$node->language][0]['value']   = $to;
    $node->field_subject[$node->language][0]['value']   = $values['subject'];
    $node->field_from[$node->language][0]['value']      = $values['from'];
    $node->field_message[$node->language][0]['value']   = $values['message'];
    
    // Get current date and format and save
    $today = getdate();
    $today_str = $today['mon'] . '/' . $today['mday'] . '/' . $today['year'];
    $node->field_date_sent[$node->language][0]['value'] = $today_str;
    
    node_save($node);
  }
  else {
    drupal_set_message(t('There was a problem sending your individual message and it was not sent.'), 'error');
  }
  
  return $result;
}

/**
 * Sends an payment received e-mail.
 *
 * @param $form_values
 *   An array of values from the contact form fields that were submitted.
 *   There are just two relevant items: ['email'] and ['message'].
 */
function email_payment_received_send($values) {
  // All system mails need to specify the module and template key (mirrored from
  // hook_mail()) that the message they want to send comes from.
  $module = 'retreatform';
  $key = 'payment_received';

  // Specify 'to' and 'from' addresses.
  $to = $values['email'];
  $from = variable_get('site_mail', 'admin@acimstlouis.org');
    
  // "params" loads in additional context for email content completion in
  // hook_mail(). In this case, we want to pass in the values the user entered
  // into the form, which include the message body in $form_values['message'].
  $params = $values;

  $language = language_default();

  $send = TRUE;

  $result = drupal_mail($module, $key, $to, $language, $params, $from, $send);
  if ($result['result'] == TRUE) {
    drupal_set_message(t('The payment received message has been sent.'));
  }
  else {
    drupal_set_message(t('There was a problem sending the payment received message and it was not sent.'), 'error');
  }
  
  return $result;
}

/**
 * Implement hook_mail_alter().
 */
function retreatform_mail_alter(&$message) {
  // Attach a site signature.
  $options = array(
    'langcode' => $message['language']->language,
  );
  
  $signature = t("\n------------------------\nACIM St. Louis");
  if (is_array($message['body'])) {
    $message['body'][] = $signature;
  }
  else {  // Some modules use the body as a string, erroneously.
    $message['body'] .= $signature;
  }
}
