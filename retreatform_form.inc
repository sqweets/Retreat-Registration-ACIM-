<?php

/**
 * This is the main file for the retreat form. This file
 * has the code for the form itself and all of the validation,
 * paging and submission (node_save) functions.
 *
 * 
 * The other files are:
 * 
 * retreatform_utilities
 *   - funcitons that return an array of state codes, etc.
 * 
 * retreatform_database
 *   - functions that access the database.
 * 
 * retreatform_mail
 *   - functions that format and send emails.
 * 
 */

require_once("retreatform_defines.inc");
require_once("retreatform_utilities.inc");
require_once("retreatform_database.inc");
require_once("retreatform_mail.inc"); 

/**
 * Regular registration
 */
function form_registration($form, &$form_state) {

  // If all registrations closeed, don't display the form, just messages
  if (RETREAT_COMMUTER_REG_MET != 'Yes') {

    // Display page 2 if $form_state['page_num'] == 2
    if (!empty($form_state['page_num']) && $form_state['page_num'] == 2) {
      return form_registration_page_two($form, $form_state);
    }
    // Display page 3 if $form_state['page_num'] == 3
    if (!empty($form_state['page_num']) && $form_state['page_num'] == 3) {
      return form_registration_page_three($form, $form_state);
    }

    // Otherwise we build page 1.
    $form_state['page_num'] = 1;
    
    // Need an all options full check here?
    $form['description_page1'] = array(
      '#type' => 'item',
      '#title' => t('<< Page 1 of 3 >>'),
    );
    
    // Setup header message based on which dates met and which options configured
    // Totally closed is checked above.
    if (EB_OPTION == 'No' && LODGING_DEADLINE_OPTION == 'No') {
      if (RETREAT_COMMUTER_REG_MET == 'No') {
        $form['one_deadline_headline'] = array(
            '#markup' => t('<p style="text-align: center;"><br><span style="font-size: 16px;"><strong>Registration Deadline is !commuter_date</strong></span></p></br>', array('!commuter_date' => RETREAT_COMMUTER_DEADLINE)),
        );
      }
    } else if (EB_OPTION == 'Yes' && LODGING_DEADLINE_OPTION == 'No') {
      if (RETREAT_EB_REG_MET == 'No') {
        // Early bird date not yet met
        $form['pre_eb_header'] = array(
            '#markup' => t('<h2 style="text-align: center;">Early Bird Registration Rate Deadline is !eb_date</h2><p style="text-align: center;"><span style="font-size: 16px;">(Your registration form and full payment must be received by that date.)</span></p>
                            <p style="text-align: center;"><br><span style="font-size: 16px;"><strong>Retreat Registration Deadline is !commuter_date</strong></span></p></br>', array('!eb_date' => RETREAT_EB_DEADLINE, '!commuter_date' => RETREAT_COMMUTER_DEADLINE)),
        );
      } else if (RETREAT_COMMUTER_REG_MET == 'No') {
        $form['one_deadline_headline'] = array(
            '#markup' => t('<p style="text-align: center;"><br><span style="font-size: 16px;"><strong>Registration Deadline is !commuter_date</strong></span></p></br>', array('!commuter_date' => RETREAT_COMMUTER_DEADLINE)),
        );
      }
    } else if (EB_OPTION == 'No' && LODGING_DEADLINE_OPTION == 'Yes') {
      if (RETREAT_LODGING_REG_MET == 'No') {
        $form['post_eb_header'] = array(
            '#markup' => t('<p style="text-align: center;"><br><span style="font-size: 16px;"><strong>Retreat Lodging Registration Deadline is !lodging_date</strong></span></p>
                            <p style="text-align: center;"><br><span style="font-size: 16px;"><strong>Retreat Commuter Registration Deadline is !commuter_date</strong></span></p></br>', array('!lodging_date' => RETREAT_LODGING_DEADLINE, '!commuter_date' => RETREAT_COMMUTER_DEADLINE)),
        );
      } else if (RETREAT_COMMUTER_REG_MET == 'No') {
        $form['post_lodging_header'] = array(
            '#markup' => t('<p style="text-align: center;"><br><span style="font-size: 16px;"><strong>Retreat Commuter Registration Deadline is !commuter_date</strong></span></p></br>', array('!commuter_date' => RETREAT_COMMUTER_DEADLINE)),
        );
      }
    } else {
      // All options and dates
      if (RETREAT_EB_REG_MET == 'No') {
        // Early bird date not yet met
        $form['pre_eb_header'] = array(
            '#markup' => t('<h2 style="text-align: center;">Early Bird Registration Rate Deadline is !eb_date</h2><p style="text-align: center;"><span style="font-size: 16px;">(Your registration form and full payment must be received by that date.)</span></p>
                            <p style="text-align: center;"><br><span style="font-size: 16px;"><strong>Retreat Lodging Registration Deadline is !lodging_date</br>
                            Retreat Commuter Registration Deadline is !commuter_date</strong></u></span></p></br>', array('!eb_date' => RETREAT_EB_DEADLINE, '!lodging_date' => RETREAT_LODGING_DEADLINE, '!commuter_date' => RETREAT_COMMUTER_DEADLINE)),
        );
      } else if (RETREAT_LODGING_REG_MET == 'No') {
        $form['post_eb_header'] = array(
            '#markup' => t('<p style="text-align: center;"><br><span style="font-size: 16px;"><strong>Retreat Lodging Registration Deadline is !lodging_date</strong></span></p>
                            <p style="text-align: center;"><br><span style="font-size: 16px;"><strong>Retreat Commuter Registration Deadline is !commuter_date</strong></span></p></br>', array('!lodging_date' => RETREAT_LODGING_DEADLINE, '!commuter_date' => RETREAT_COMMUTER_DEADLINE)),
        );
      } else if (RETREAT_COMMUTER_REG_MET == 'No') {
        $form['post_lodging_header'] = array(
            '#markup' => t('<p style="text-align: center;"><br><span style="font-size: 16px;"><strong>Retreat Commuter Registration Deadline is !commuter_date</strong></span></p></br>', array('!commuter_date' => RETREAT_COMMUTER_DEADLINE)),
        );
      }
    }
  
    $form['contact_info'] = array(
      '#type' => 'fieldset',
      '#title' => t('Name and Contact Information'),
      '#states' => array('visible' => TRUE),
    );
    $form['contact_info']['first'] = array(
      '#type' => 'textfield',
      '#title' => t('First name'),
      '#size' => 60,
      '#maxlength' => 25,
      '#required' => TRUE,
      '#default_value' => !empty($form_state['values']['first']) ? t($form_state['values']['first']) : t(''),
    );
    $form['contact_info']['last'] = array(
      '#type' => 'textfield',
      '#title' => t('Last name'),
      '#size' => 60,
      '#maxlength' => 25,
      '#required' => TRUE,
      '#default_value' => !empty($form_state['values']['last']) ? t($form_state['values']['last']) : t(''),
    );
    $form['contact_info']['address'] = array(
      '#type' => 'textfield',
      '#title' => t('Address'),
      '#size' => 60,
      '#maxlength' => 25,
      '#required' => TRUE,
      '#default_value' => !empty($form_state['values']['address']) ? t($form_state['values']['address']) : t(''),
    );
    $form['contact_info']['address2'] = array(
      '#type' => 'textfield',
      '#title' => t('Address 2'),
      '#size' => 60,
      '#maxlength' => 25,
      '#default_value' => !empty($form_state['values']['address2']) ? t($form_state['values']['address2']) : t(''),
    );
    $form['contact_info']['city'] = array(
      '#type' => 'textfield',
      '#title' => t('City'),
      '#size' => 60,
      '#maxlength' => 25,
      '#required' => TRUE,
      '#default_value' => !empty($form_state['values']['city']) ? t($form_state['values']['city']) : t(''),
    );
    $form['contact_info']['state'] = array(
      '#title' => t('State'),
      '#type' => 'select',
      '#options' => options_united_states(),
      '#required' => TRUE,
      '#default_value' => !empty($form_state['values']['state']) ? t($form_state['values']['state']) : t('MO'),
    );
    $form['contact_info']['zip_code'] = array(
      '#type' => 'textfield',
      '#title' => t('Zip Code'),
      '#size' => 5,
      '#maxlength' => 5,
      '#required' => TRUE,
      '#default_value' => !empty($form_state['values']['zip_code']) ? t($form_state['values']['zip_code']) : t(''),
    );
    $form['contact_info']['phone'] = array(
      '#type' => 'textfield',
      '#title' => t('Phone Number'),
      '#size' => 10,
      '#maxlength' => 10,
      '#description' => t('Enter only numbers: 3145551234'),
      '#required' => TRUE,
      '#default_value' => !empty($form_state['values']['phone']) ? t($form_state['values']['phone']) : t(''),
    );
    $form['contact_info']['email'] = array(
      '#type' => 'textfield',
      '#title' => t('Email'),
      '#size' => 40,
      '#maxlength' => 40,
      '#required' => TRUE,
      '#default_value' => !empty($form_state['values']['email']) ? t($form_state['values']['email']) : t(''),
    );
    $form['next_one'] = array(
      '#type' => 'submit',
      '#value' => t('Next >>'),
      '#validate' => array('form_registration_next_validate'),
      '#submit' => array('form_registration_next_submit'),
    );
  } else {
    $form['reg_closed'] = array(
      '#markup' => t('<h2 style="text-align: center;">Online registration is now closed.</h2><p style="text-align: center;"><span style="font-size: 14px;"><strong>!retreat_closed_msg</strong></span></p></br>', array('!retreat_closed_msg' => RETREAT_CLOSED_MSG)),
    );
  }

  return $form;
}



/**
 * Returns the form for the second page of form_registration().
 */
function form_registration_page_two($form, &$form_state) {

  global $only_roommate_names;

  $form['description_page2'] = array(
    '#type' => 'item',
    '#title' => t('<< Page 2 of 3 >>'),
  );

  $form['reginfo'] = array(
    '#type' => 'fieldset',
    '#title' => t('Registration Information'),
    '#required' => TRUE,
    '#states' => array('visible' => TRUE),
  );
  $form['reginfo']['option'] = array(
    '#type' => 'radios',
    '#title' => t('Option'),
    '#options' => options_rooms(),
    '#required' => TRUE,
    '#default_value' => !empty($form_state['values']['option']) ? t($form_state['values']['option']) : t(OPTION_1),
  );
  
  // If the lodging date has not passed, allow all registrations
  // Only check if configured to have both lodging and commuter deadlines
  if (RETREAT_LODGING_REG_MET == 'No' || LODGING_DEADLINE_OPTION == 'No') {
    // Determine if any room options need to be disabled
    // and update option text with number of available spots
    // the #options were sanitized when in the options_rooms() function.
    // same for the option#_remaining() functions
    if (option1_remaining() <= 0) {
      $form['reginfo']['option'][OPTION_1]['#disabled'] =  TRUE;
      $form['reginfo']['option']['#options'][OPTION_1] = $form['reginfo']['option']['#options'][OPTION_1] . STR_FOR_COST . room_costs(OPTION_1) . t(' - NONE AVAILABLE');
    } else {
      $form['reginfo']['option'][OPTION_1]['#disabled'] =  FALSE;
      $form['reginfo']['option']['#options'][OPTION_1] = $form['reginfo']['option']['#options'][OPTION_1] . STR_FOR_COST . room_costs(OPTION_1) . t(' - ') . option1_remaining() . t(' available');
    }

    if (option3_remaining() <= 0) {
      $form['reginfo']['option'][OPTION_3]['#disabled'] =  TRUE;
      $form['reginfo']['option']['#options'][OPTION_3] = $form['reginfo']['option']['#options'][OPTION_3] . STR_FOR_COST . room_costs(OPTION_3) . t(' - NONE AVAILABLE');
    } else {
      $form['reginfo']['option'][OPTION_3]['#disabled'] =  FALSE;
      
      $temp = array_values(options_roommates());
      $last_roommate = $temp[0];
      
      if (($only_roommate_names == TRUE) && (option3_remaining() == 1)) {
        $form['reginfo']['option']['#options'][OPTION_3] = $form['reginfo']['option']['#options'][OPTION_3] . STR_FOR_COST . room_costs(OPTION_3) . t(" - available for $last_roommate") . t("'s roommate only");
      } else {
        $form['reginfo']['option']['#options'][OPTION_3] = $form['reginfo']['option']['#options'][OPTION_3] . STR_FOR_COST . room_costs(OPTION_3) . t(' - ') . option3_remaining() . t(' available');
      }
    }
  }
 
  if (option4_remaining() <= 0) {
    $form['reginfo']['option'][OPTION_4]['#disabled'] =  TRUE;
    $form['reginfo']['option']['#options'][OPTION_4] = $form['reginfo']['option']['#options'][OPTION_4] . t(' - NONE AVAILABLE');
  } else {
    $form['reginfo']['option'][OPTION_4]['#disabled'] =  FALSE;
    $form['reginfo']['option']['#options'][OPTION_4] = $form['reginfo']['option']['#options'][OPTION_4] . STR_FOR_COST . room_costs(OPTION_4) . t(' - ') . option4_remaining() . t(' available');
  }

  // Check to see if OPTION 5 is available
  if (SATURDAY == 'Yes') {
    if (option5_remaining() <= 0) {
      $form['reginfo']['option'][OPTION_5]['#disabled'] =  TRUE;
      $form['reginfo']['option']['#options'][OPTION_5] = $form['reginfo']['option']['#options'][OPTION_5] . t(' - NONE AVAILABLE');
    } else {
      $form['reginfo']['option'][OPTION_5]['#disabled'] =  FALSE;
      $form['reginfo']['option']['#options'][OPTION_5] = $form['reginfo']['option']['#options'][OPTION_5] . STR_FOR_COST . room_costs(OPTION_5) . t(' - ') . option5_remaining() . t(' available');
    }
  }

  // Check to see if OPTION 6 is available
  if (HALFDAY == 'Yes') {
    if (option6_remaining() <= 0) {
      $form['reginfo']['option'][OPTION_6]['#disabled'] =  TRUE;
      $form['reginfo']['option']['#options'][OPTION_6] = $form['reginfo']['option']['#options'][OPTION_6] . t(' - NONE AVAILABLE');
    } else {
      $form['reginfo']['option'][OPTION_6]['#disabled'] =  FALSE;
      $form['reginfo']['option']['#options'][OPTION_6] = $form['reginfo']['option']['#options'][OPTION_6] . STR_FOR_COST . room_costs(OPTION_6) . t(' - ') . option6_remaining() . t(' available');
    }
  }

  // Determine new default value
  // Skip if there is already a value
  if (empty($form_state['values']['option']['#default_value'])) {
    
    // If the lodging date has not passed or if there is no lodging deadline, allow all registrations
    if (RETREAT_LODGING_REG_MET == 'No' || LODGING_DEADLINE_OPTION == 'No') {
      if ($form['reginfo']['option'][OPTION_1]['#disabled'] == FALSE) {
        $form['reginfo']['option']['#default_value'] = OPTION_1;
      // } else if ($form['reginfo']['option'][OPTION_2]['#disabled'] == FALSE && OPT_2_OPTION == 'Yes') {
      //   $form['reginfo']['option']['#default_value'] = OPTION_2;
      } else if ($form['reginfo']['option'][OPTION_3]['#disabled'] == FALSE) {
        $form['reginfo']['option']['#default_value'] = OPTION_3;
      } else if ($form['reginfo']['option'][OPTION_4]['#disabled'] == FALSE) {
        $form['reginfo']['option']['#default_value'] = OPTION_4;
      } else if (($form['reginfo']['option'][OPTION_5]['#disabled'] == FALSE) && (SATURDAY == 'Yes')) {
        $form['reginfo']['option']['#default_value'] = OPTION_5;
      } else if (($form['reginfo']['option'][OPTION_6]['#disabled'] == FALSE) && (HALFDAY == 'Yes')) {
        $form['reginfo']['option']['#default_value'] = OPTION_6;
      } else {
        $form['reginfo']['option']['default_value'] = '';
      }
    }
    else {
      if ($form['reginfo']['option'][OPTION_4]['#disabled'] == FALSE) {
        // Commuter available
        $form['reginfo']['option']['#default_value'] = OPTION_4;
      } else if (($form['reginfo']['option'][OPTION_5]['#disabled'] == FALSE) && (SATURDAY == 'Yes')) {
        // Saturday Commuter available
        $form['reginfo']['option']['#default_value'] = OPTION_5;
      } else if (($form['reginfo']['option'][OPTION_6]['#disabled'] == FALSE) && (HALFDAY == 'Yes')) {
        // Saturday Half Day available
        $form['reginfo']['option']['#default_value'] = OPTION_6;
      }
    }
  }

  if (!empty($form_state['values']['roommate'])) {
    $form['reginfo']['roommate'] = array(
      '#type' => 'select',
      '#title' => t('Name of Roommate'),
      '#description' => t('Choose an option or name from the selection list'),
      '#options' => options_roommates(),
      '#states' => array(
        'visible' => array(
          ':input[name="option"]' => array('value' => OPTION_3),
        ),
      ),
      '#default_value' => $form_state['values']['roommate'],
    );
  } else {
    $form['reginfo']['roommate'] = array(
      '#type' => 'select',
      '#title' => t('Name of Roommate'),
      '#description' => t('Choose an option or name from the selection list'),
      '#options' => options_roommates(),
      '#states' => array(
        'visible' => array(
          ':input[name="option"]' => array('value' => OPTION_3),
        ),
      ),
    );
  }
  
  $form['reginfo']['meal'] = array(
    '#title' => t('Dietary meal needs (We will do our best to accommodate them):'),
    '#type' => 'select',
    '#options' => options_meal(),
    '#required' => TRUE,
    '#default_value' => !empty($form_state['values']['meal']) ? t($form_state['values']['meal']) : t('None'),
  );
  $form['reginfo']['meal_details'] = array(
    '#type' => 'textarea',
    '#title' => t('Explain other meal needs here:'),
    '#size' => 60,
    '#maxlength' => 200,
    '#states' => array(
      'visible' => array(
        ':input[name="meal"]' => array('value' => 'Other (please explain)'),
      ),
    ),
    '#default_value' => !empty($form_state['values']['meal_details']) ? t($form_state['values']['meal_details']) : t(''),
  );
  
  $form['reginfo']['special_needs'] = array(
    '#title' => t('Do you have any special needs?'),
    '#type' => 'select',
    '#options' => array('No' => t('No'), 'Yes' => t('Yes')),
    '#required' => TRUE,
    '#default_value' => !empty($form_state['values']['special_needs']) ? t($form_state['values']['special_needs']) : t('No'),
  );
  $form['reginfo']['needs_info'] = array(
    '#type' => 'textarea',
    '#title' => t('Explain special needs here:'),
    '#size' => 60,
    '#maxlength' => 40,
    '#states' => array(
      'visible' => array(
        ':input[name="special_needs"]' => array('value' => 'Yes'),
      ),
    ),
    '#default_value' => !empty($form_state['values']['needs_info']) ? t($form_state['values']['needs_info']) : t(''),
  );

  $form['reginfo']['how_heard'] = array(
    '#type' => 'radios',
    '#title' => t('How did you hear about the Retreat?'),
    '#options' => options_how_heard(),
    '#required' => TRUE,

    '#default_value' => !empty($form_state['values']['how_heard']) ? t($form_state['values']['how_heard']) : t(''),
  );

  $form['reginfo']['how_heard_other_text'] = array(
    '#type' => 'textarea',
    '#states' => array(
      'visible' => array(
        ':input[name="how_heard"]' => array('value' => 'Other'),
      ),
      '#required' => TRUE,
    ),
    '#default_value' => !empty($form_state['values']['how_heard_other_text']) ? t($form_state['values']['how_heard_other_text']) : t(''),
  );

  if (SCHOLARSHIP_OPTION == 'Yes') {
    $form['reginfo']['donation_text'] = array(
      '#markup' => t('<p><strong>Please consider making a donation to the Ruth Hanna Scholarship Fund which offers assistance to others in need of financial support to attend this event. To make a donation simply fill in the amount you wish to give below and that amount will be added to your registration fee. If you do not wish to donate at this time simply leave a zero in the donation field. Thank you! (A limited number of scholarships will be available for this event.)</strong></p>'),
    );
    
    $form['reginfo']['donation'] = array(
      '#type' => 'textfield',
      '#title' => t('Donation Amount'),
      '#description' => t('Enter only numbers and only a whole dollar amount'),
      '#size' => 10,
      '#maxlength' => 10,
      '#field_prefix' => t('$'),
      '#default_value' => !empty($form_state['values']['donation']) ? t($form_state['values']['donation']) : t('0'),
    );
  }

  $form['form_of_payment'] = array(
    '#title' => t('Form of Payment'),
    '#type' => 'radios',
    '#options' => options_payment(),
    '#required' => TRUE,
    '#default_value' => !empty($form_state['values']['form_of_payment']) ? t($form_state['values']['form_of_payment']) : t('PayPal'),
  );
  if (DISPLAY_SCHOLARSHIP_OPTION == 'No') {
    $form['payment_scholorship_off_text'] = array(
      '#markup' => t('Requests for scholarship are no longer being received as of May 1st.<br><br>'),
    );
  }
 
  
  $form['back_two'] = array(
    '#type' => 'submit',
    '#value' => t('<< Back'),
    '#submit' => array('form_registration_page_two_back'),
  );

  $form['next_two'] = array(
    '#type' => 'submit',
    '#value' => t('Next >>'),
    '#submit' => array('form_registration_page_two_next_submit'),
    '#validate' => array('form_registration_page_two_next_validate'),
  );

  return $form;
}

/**
 * Returns the form for the third page of form_registration().
 * This page prints all inputs and asks the user to verify and update as needed.
 */
function form_registration_page_three($form, &$form_state) {
  $page_one_values = $form_state['page_values'][1];
  $page_two_values = $form_state['page_values'][2];
  
  $phone_number['phone_a'] = substr($page_one_values['phone'], 0, 3);
  $phone_number['phone_b'] = substr($page_one_values['phone'], 3, 3);
  $phone_number['phone_c'] = substr($page_one_values['phone'], 6, 4);
  
  $form['description_page3'] = array(
    '#type' => 'item',
    '#title' => t('<< Page 3 of 3 >>'),
  );
  $form['validate'] = array(
    '#markup' => t('<p><span style="font-size: 16px;"><strong>Please verify your inputs below and update as needed</strong></span></p><br>'),
  );
  
  $form['contact_info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Name and Contact Information'),
    '#states' => array('visible' => TRUE),
  );
  
  if ($page_one_values['address2'] != '') {
    $form['contact_info']['print_address'] = array(
      '#markup' => t("<p>@first @last<br>@address<br>@address2<br>@city, @state   @zip_code<br>(@phone1) @phone2-@phone3<br>@email</p>", 
        array('@first' => $page_one_values['first'],
              '@last' => $page_one_values['last'],
              '@address' => $page_one_values['address'],
              '@address2' => $page_one_values['address2'],
              '@city' => $page_one_values['city'],
              '@state' => $page_one_values['state'],
              '@zip_code' => $page_one_values['zip_code'],
              '@phone1' => $phone_number['phone_a'],
              '@phone2' => $phone_number['phone_b'],
              '@phone3' => $phone_number['phone_c'],
              '@email' => $page_one_values['email'])),
    );
  } else {
    $form['contact_info']['print_address'] = array(
      '#markup' => t("<p>@first @last<br>@address<br>@city, @state   @zip_code<br>(@phone1) @phone2-@phone3<br>@email</p>", 
        array('@first' => $page_one_values['first'],
              '@last' => $page_one_values['last'],
              '@address' => $page_one_values['address'],
              '@city' => $page_one_values['city'],
              '@state' => $page_one_values['state'],
              '@zip_code' => $page_one_values['zip_code'],
              '@phone1' => $phone_number['phone_a'],
              '@phone2' => $phone_number['phone_b'],
              '@phone3' => $phone_number['phone_c'],
              '@email' => $page_one_values['email'])),
    );
  }
  
  // Change button for contact info
  $form['change_contact'] = array(
    '#type' => 'submit',
    '#value' => t('Change Contact Information'),
    '#submit' => array('form_registration_back_to_page_one'),
  );

  $form['space1'] = array(
    '#markup' => t('<br><br>'),
  );

  $form['registration_info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Registration Information'),
    '#states' => array('visible' => TRUE),
  );
  
  
  $form['registration_info']['registration1'] = array(
     '#markup' => t("<p>Room Option:  @option", 
     array('@option' => $page_two_values['option'] . STR_FOR_COST . room_costs($page_two_values['option']))),
  );

  if ($page_two_values['option'] == OPTION_3) {
    if ($page_two_values['roommate'] != 'not matched') {  
      $roommate_array = options_roommates();
      $roommate = $roommate_array[$page_two_values['roommate']];
    } else if ($page_two_values['roommate'] == 'not matched') {
      $roommate = 'My roommate has not registered yet';
    } else {
      $roommate = $page_two_values['roommate'];
    }
    
    $form['registration_info']['registration2'] = array(
       '#markup' => t("<br>Roommate's Name:  @roommate", 
       array('@roommate' => $roommate)),
    );
  }
  $form['registration_info']['registration3'] = array(
     '#markup' => t("<br>Meal Needs:  @meal", 
     array('@meal' => $page_two_values['meal'])),
  );
  if ($page_two_values['meal'] == 'Other (please explain)') {
    $form['registration_info']['registration4'] = array(
       '#markup' => t("<br>Meal Details:  @meal_details", 
       array('@meal_details' => $page_two_values['meal_details'])),
    );
  }
  $form['registration_info']['registrationA'] = array(
     '#markup' => t("<br>Special Needs:  @special_needs", 
     array('@special_needs' => $page_two_values['special_needs'])),
  );
  if ($page_two_values['special_needs'] == 'Yes') {
    $form['registration_info']['registrationB'] = array(
       '#markup' => t("<br>Special Needs Details:  @needs_info", 
       array('@needs_info' => $page_two_values['needs_info'])),
    );
  }
  
  if (SCHOLARSHIP_OPTION == 'Yes') {
    $form['registration_info']['registration5'] = array(
       '#markup' => t("<br>Donation:  $@donation<br>Form of Payment:  @form_of_payment</p>", 
       array('@donation' => $page_two_values['donation'],
             '@form_of_payment' => $page_two_values['form_of_payment'])),
    );
  } else {
    $form['registration_info']['registration5'] = array(
       '#markup' => t("<br>Form of Payment:  @form_of_payment</p>", 
       array('@form_of_payment' => $page_two_values['form_of_payment'])),
    );
  }

  // change button for registration info
  $form['change_registration'] = array(
    '#type' => 'submit',
    '#value' => t('Change Registration Information'),
    '#submit' => array('form_registration_back_to_page_two'),
  );

  $form['space'] = array(
    '#markup' => t('<br><br><hr />'),
  );

  if (DISPLAY_SCHOLARSHIP_OPTION == 'No') {
    $form['instructions'] = array(
     '#markup' => t('<strong><p>Once you have verified all your inputs are correct you are ready to submit your registration.
                     <br>If you elected to pay via (PayPal) you will be redirected to the PayPal website.
                     <br>If you elected to pay via (mail) you will receive a separate form email to print and send with your payment.</p></strong><br>'),
     );
  } else {
    $form['instructions'] = array(
     '#markup' => t('<strong><p>Once you have verified all your inputs are correct you are ready to submit your registration.
                     <br>If you elected to pay via (PayPal) you will be redirected to the PayPal website.
                     <br>If you elected to pay via (mail) you will receive a separate form email to print and send with your payment.
                     <br>If you elected to request a (scholarship) you will be redirected to the scholarship application form.</p></strong><br>'),
     );
  }
  
  $form['submit'] = array(
    '#prefix' => '<div class="registration-submit">',
    '#suffix' => '</div>',
    '#type' => 'submit',
    '#value' => t('<< Submit Registration >>'),
    '#submit' => array('form_registration_page_three_submit'),
  );

  return $form;
}


/**
 * Validate handler for the next button on first page.
 */
function form_registration_next_validate($form, &$form_state) {
  $zip_code = $form_state['values']['zip_code'];
  if (!is_numeric($zip_code)) {
    form_set_error('zip_code', t('Please only enter numbers for the zip code.'));
  }
  
  $phone = $form_state['values']['phone'];
  if (!is_numeric($phone)) {
    form_set_error('phone', t('Please only enter numbers for the phone number.'));
  }
  
  $email = $form_state['values']['email'];
  if (!valid_email_address($email)) {
    form_set_error('email', t('Please enter a valid email address.'));
  }
  
  // Check for duplicate entry
  $identity = array('first' => $form_state['values']['first'],
                    'last' => $form_state['values']['last'],
                    'email' => $form_state['values']['email']);
  if (match_entry($identity) != 0) {
    form_set_error('first', t('There is already an entry in the database for that first name, '));
    form_set_error('last', t('last name and email address.'));
    form_set_error('email', t("Please see the \"Where to Get Help\" option in the Retreat Menu if your registration isn't a duplicate."));
  }
}


/**
 * Validate handler for the next button on second page.
 */
function form_registration_page_two_next_validate($form, &$form_state) {

  if (SCHOLARSHIP_OPTION == 'Yes') {
    $donation = $form_state['values']['donation'];
    if (!is_numeric($donation)) {
      form_set_error('donation', t('Please only enter numbers for the donation value.'));
    }
    if (strstr($donation, '.')) {
      $temp = strpos($donation, '.');
      $form_state['values']['donation'] = substr($donation, 0, $temp);
    }
  }
  
  $option = $form_state['values']['option'];
  $roommate = $form_state['values']['roommate'];
  if (($option == OPTION_3) && 
      ($roommate == '')) {
     form_set_error('roommate', t('Please enter a roommate name or select another room option.'));
  }
  
  $meal = $form_state['values']['meal'];
  $meal_details = $form_state['values']['meal_details'];
  if (($meal == 'Other (please explain)') && 
      ($meal_details == '')) {
     form_set_error('meal_details', t('Please enter explaination of meal needs or select another meal option.'));
  }

  $special_needs = $form_state['values']['special_needs'];
  $needs_details = $form_state['values']['needs_info'];
  if (($special_needs == 'Yes') && ($needs_details == '')) {
     form_set_error('needs_info', t('Please enter explaination of special needs or select no special needs.'));
  }
}

/**
 * Submit handler for form_registration() next button.
 *
 * Capture the values from page one and store them away so they can be used
 * at final submit time.
 */
function form_registration_next_submit($form, &$form_state) {

  // Values are saved for each page.
  // to carry forward to subsequent pages in the form.
  // and we tell FAPI to rebuild the form.
  $form_state['page_values'][1] = $form_state['values'];

  if (!empty($form_state['page_values'][2])) {
    $form_state['values'] = $form_state['page_values'][2];
  }

  // When form rebuilds, it will look at this to figure which page to build.
  $form_state['page_num'] = 2;
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit handler for form_registration() page 2 next button.
 *
 * Capture the values from page two and store them away so they can be used
 * at final submit time.
 */
function form_registration_page_two_next_submit($form, &$form_state) {

  // Values are saved for each page.
  // to carry forward to subsequent pages in the form.
  // and we tell FAPI to rebuild the form.
  $form_state['page_values'][2] = $form_state['values'];

  // Clear roommate and meal details fields if they should be
  if ($form_state['page_values'][2]['option'] != OPTION_3) {
    $form_state['page_values'][2]['roommate'] = t('');
  }
  if ($form_state['page_values'][2]['meal'] != 'Other (please explain)') {
    $form_state['page_values'][2]['meal_details'] = t('');
  }
  if ($form_state['page_values'][2]['special_needs'] != 'Yes') {
    $form_state['page_values'][2]['needs_info'] = t('');
  }
   
  // When form rebuilds, it will look at this to figure which page to build.
  $form_state['page_num'] = 3;
  $form_state['rebuild'] = TRUE;
}

/**
 * Back button handler submit handler.
 */
function form_registration_page_two_back($form, &$form_state) {
  $form_state['page_values'][2] = $form_state['values'];

  $form_state['values'] = $form_state['page_values'][1];
  $form_state['page_num'] = 1;
  $form_state['rebuild'] = TRUE;
}

/**
 * Back button handler submit handler from page 3.
 */
function form_registration_back_to_page_one($form, &$form_state) {
  $form_state['values'] = $form_state['page_values'][1];
  $form_state['page_num'] = 1;
  $form_state['rebuild'] = TRUE;
}
/**
 * Back button handler submit handler from page 3.
 */
function form_registration_back_to_page_two($form, &$form_state) {
  $form_state['values'] = $form_state['page_values'][2];
  $form_state['page_num'] = 2;
  $form_state['rebuild'] = TRUE;
}

/**
 * The page 3 submit handler.
 *
 * This is the final submit handler. The form data is saved to a node,
 * the confirmation email is sent and the user is redirected to either
 * paypal or a printable form.
 */
function form_registration_page_three_submit($form, &$form_state) {
  $page_one_values = $form_state['page_values'][1];
  $page_two_values = $form_state['page_values'][2];
  
  // Check for duplicate entry
  $identity = array('first' => $page_one_values['first'],
                    'last' => $page_one_values['last'],
                    'email' => $page_one_values['email']);
  if (match_entry($identity) == 0) {
    // Create a node object and save it
    $node = new stdClass();
    $node->type = 'retreat_registration';
    node_object_prepare($node);
  
    // save title as lastname, firstname
    $node->title    = $page_one_values['last'] . ', ' . $page_one_values['first'];
    $node->language = LANGUAGE_NONE;

    // save retreat year
    $node->field_year_of_retreat[$node->language][0]['value']    = YEAR;
    // save the current date
    $today = getdate();
    $today_str = $today['mon'] . '/' . $today['mday'] . '/' . $today['year'];
    $node->field_registration_date[$node->language][0]['value'] = $today_str;
    // save form values
    $node->field_first_name[$node->language][0]['value']    = $page_one_values['first'];
    $node->field_last_name[$node->language][0]['value']     = $page_one_values['last'];
    $node->field_address[$node->language][0]['value']       = $page_one_values['address'];
    $node->field_address_2[$node->language][0]['value']     = $page_one_values['address2'];
    $node->field_city[$node->language][0]['value']          = $page_one_values['city'];
    $node->field_state[$node->language][0]['value']         = $page_one_values['state'];
    $node->field_zip_code[$node->language][0]['value']      = $page_one_values['zip_code'];
    $node->field_postal_code[$node->language][0]['value']   = $page_one_values['postal_code'];
    $node->field_phone_number[$node->language][0]['value']  = $page_one_values['phone'];
    $node->field_email_address[$node->language][0]['value'] = $page_one_values['email'];
    $node->field_room_option[$node->language][0]['value']   = $page_two_values['option'];
    $node->field_roommate[$node->language][0]['value']      = $page_two_values['roommate'];
    $node->field_meal_needs[$node->language][0]['value']    = $page_two_values['meal'];
    $node->field_meal_info[$node->language][0]['value']     = $page_two_values['meal_details'];
    $node->field_special_needs[$node->language][0]['value'] = $page_two_values['special_needs'];
    $node->field_needs_info[$node->language][0]['value']    = $page_two_values['needs_info'];
    $node->field_notes[$node->language][0]['value']         = $page_one_values['country'];
    
    if (SCHOLARSHIP_OPTION == 'Yes') {
      $node->field_donation[$node->language][0]['value']      = $page_two_values['donation'];
    } else {
      $node->field_donation[$node->language][0]['value']      = 0;
    }
    $node->field_heard[$node->language][0]['value']         = $page_two_values['how_heard'];
    $node->field_heard_other_text[$node->language][0]['value'] = $page_two_values['how_heard_other_text'];
    $node->field_form_payment[$node->language][0]['value']  = $page_two_values['form_of_payment'];
    
    if ($page_two_values['option'] == OPTION_4) {
      $node->field_room_number[$node->language][0]['value']  = 'Commuter';
    }
    
    if ($page_two_values['option'] == OPTION_5) {
      $node->field_room_number[$node->language][0]['value']  = 'Saturday Commuter';
    }

    if ($page_two_values['option'] == OPTION_6) {
      $node->field_room_number[$node->language][0]['value']  = 'Saturday Half Day';
    }

    // Compute total due
    if (SCHOLARSHIP_OPTION == 'Yes') {
      $total = t("(@total)", array('@total' => (room_costs($page_two_values['option']) + intval($page_two_values['donation']))));
    } else {
      $total = t("(@total)", array('@total' => (room_costs($page_two_values['option']))));
    }
    
    $node->field_payment_received[$node->language][0]['value']  = $total;
    
    $path = 'content/programmatically_created_node_' . date('YmdHis');
    $node->path = array('alias' => $path);

    // Set scholarship checkboxes
    if ($page_two_values['form_of_payment'] == 'Scholarship') {
      $node->field_scholarship_received[$node->language][0]['value'] = '1';
      $node->field_don_t_send_payment_recieve[$node->language][0]['value'] = '1';
    }
    
    // Log registration with all data
    if (SCHOLARSHIP_OPTION == 'Yes') {
      watchdog('retreatform', t("Attempting save of registration for
                              %first_name %last_name:%address|%address2|%city|%state|%zip_code|
                              %phone|%email|%option|%roommate|%meal|%meal_details|%special_needs|%needs_info|
                              %donation|%how_heard|%how_heard_other_text|%form_of_payment"),
                              array(
                              '%first_name' => $page_one_values['first'],
                              '%last_name' => $page_one_values['last'],
                              '%address' => $page_one_values['address'],
                              '%address2' => $page_one_values['address2'],
                              '%city' => $page_one_values['city'],
                              '%state' => $page_one_values['state'],
                              '%zip_code' => $page_one_values['zip_code'],
                              '%phone' => $page_one_values['phone'],
                              '%email' => $page_one_values['email'],
                              '%option' => $page_two_values['option'],
                              '%roommate' => $page_two_values['roommate'],
                              '%meal' => $page_two_values['meal'],
                              '%meal_details' => $page_two_values['meal_details'],
                              '%special_needs' => $page_two_values['special_needs'],
                              '%needs_info' => $page_two_values['needs_info'],
                              '%donation' => $page_two_values['donation'],
                              '%first_retreat' => $page_two_values['first_retreat'],
                              '%how_heard' => $page_two_values['how_heard'],
                              '%how_heard_other_text' => $page_two_values['how_heard_other_text'],
                              '%form_of_payment' => $page_two_values['form_of_payment']),
                              WATCHDOG_NOTICE);
    } else {
      watchdog('retreatform', t("Attempting save of registration for
                              %first_name %last_name:%address|%address2|%city|%state|%zip_code|
                              %phone|%email|%option|%roommate|%meal|%meal_details|%special_needs|%needs_info|
                              %how_heard|%how_heard_other_text|%form_of_payment"),
                              array(
                              '%first_name' => $page_one_values['first'],
                              '%last_name' => $page_one_values['last'],
                              '%address' => $page_one_values['address'],
                              '%address2' => $page_one_values['address2'],
                              '%city' => $page_one_values['city'],
                              '%state' => $page_one_values['state'],
                              '%zip_code' => $page_one_values['zip_code'],
                              '%phone' => $page_one_values['phone'],
                              '%email' => $page_one_values['email'],
                              '%option' => $page_two_values['option'],
                              '%roommate' => $page_two_values['roommate'],
                              '%meal' => $page_two_values['meal'],
                              '%meal_details' => $page_two_values['meal_details'],
                              '%special_needs' => $page_two_values['special_needs'],
                              '%needs_info' => $page_two_values['needs_info'],
                              '%first_retreat' => $page_two_values['first_retreat'],
                              '%how_heard' => $page_two_values['how_heard'],
                              '%how_heard_other_text' => $page_two_values['how_heard_other_text'],
                              '%form_of_payment' => $page_two_values['form_of_payment']),
                              WATCHDOG_NOTICE);
    }

    node_save($node);

    drupal_set_message(t('Your registration has been submitted.'));

    // Match roommates and store the roommate in the form_state array so its available for email
    if (($page_two_values['option'] == OPTION_3) && ($page_two_values['roommate'] != 'not matched')) {
      $form_state['page_values'][2]['roommate'] = match_roommates($node);
    }

    // Send out confirmation email
    $result = email_confirm_send($form_state['page_values']);
    
    // Log results for sending email
    if ($result['result'] == TRUE) {
      watchdog('retreatform', t("Confirmation email for %first_name %last_name sent"),
               array ('%first_name' => $page_one_values['first'], '%last_name' => $page_one_values['last']), WATCHDOG_NOTICE);
    } else {
      watchdog('retreatform', t("ERROR sending confirmation email for %first_name %last_name"),
               array ('%first_name' => $page_one_values['first'], '%last_name' => $page_one_values['last']), WATCHDOG_ERROR);
    }
    
    // Send form email
    if ($page_two_values['form_of_payment'] == 'Mail') {
      email_form_send($form_state['page_values']);
    }
    
    // Log results for sending email
    if ($result['result'] == TRUE) {
      watchdog('retreatform', t("Form email for %first_name %last_name sent"),
               array ('%first_name' => $page_one_values['first'], '%last_name' => $page_one_values['last']), WATCHDOG_NOTICE);
    } else {
      watchdog('retreatform', t("ERROR sending form email for %first_name %last_name"),
               array ('%first_name' => $page_one_values['first'], '%last_name' => $page_one_values['last']), WATCHDOG_ERROR);
    }

    // Send to scholarship application
    if ($page_two_values['form_of_payment'] == 'Scholarship') {
      drupal_goto('content/ruth-hanna-scholarship-fund-application');
    }

    // PayPal processing here
    // Build data and save in session
    if ($page_two_values['form_of_payment'] == 'PayPal') {
      build_paypal_form($page_one_values, $page_two_values);
    }
  }
  else {
    drupal_set_message(t('Your registration is already recorded.'), 'error');
  }
    // Redirect on submission, set $form_state['redirect']
    $form_state['redirect'] = 'content/thank-you';
}


/**
 * Builds the hidden form payment button then redirects to the page that has the hidden form 
 * and payment button
 *
 * Preliminary notes:
 *  - PayPal expects a state code in 2-digit caps (no full names)
 *  - Need to break phone number into three strings... [area] [3-digits] [4-digits]
 */
function build_paypal_form($page_one_values, $page_two_values) {

  $total_paymemt = room_costs($page_two_values['option']) + intval($page_two_values['donation']);
  $registration_fee = room_costs($page_two_values['option']);
  $donation = intval($page_two_values['donation']);
  $night_phone_a = intval(substr($page_one_values['phone'], 0, 3));
  $night_phone_b = intval(substr($page_one_values['phone'], 3, 3));
  $night_phone_c = intval(substr($page_one_values['phone'], 6, 4));

  // Form setup
  $block_code .= "<form action='https://www.sandbox.paypal.com/cgi-bin/webscr' method='post'>";
  $block_code .= "<input type='hidden' name='cmd' value='_cart' />";
  $block_code .= "<input type='hidden' name='business' value='elh.payment.testing@gmail.com' />";
  $block_code .= "<input type='hidden' name='item_name' value='Retreat Registration' />";
  $block_code .= "<input type='hidden' name='currency_code' value='USD' />";
  $block_code .= "<input type='hidden' name='bn' value='PP-BuyNowACIM'>";
  $block_code .= "<input type='hidden' name='tax' value='0.00' />";
  $block_code .= "<input type='hidden' name='tax_rate' value='0.00' />";
  $block_code .= "<input type='hidden' name='notify_url' value='https://acimstlouis.org/ipn'>";
  $block_code .= "<input type='hidden' name='lc' value='en_US'>";
  $block_code .= "<input type='hidden' name='cancel_return' value='https://acimstlouis.org/retreat_registration' />";
  $block_code .= "<input type='hidden' name='return' value='https://acimstlouis.org/content/thank-you' />";
  $block_code .= "<input type='hidden' name='no_shipping' value='1' />";
  $block_code .= "<input type='hidden' name='no_note' value='1' />";
  $block_code .= "<input type='hidden' name='upload' value='1' />";
  $block_code .= "<input type='hidden' name='first_name' value='{$page_one_values['first']}' />";
  $block_code .= "<input type='hidden' name='last_name' value='{$page_one_values['last']}' />";
  $block_code .= "<input type='hidden' name='address1' value='{$page_one_values['address']}' />";
  $block_code .= "<input type='hidden' name='city' value='{$page_one_values['city']}' />";
  $block_code .= "<input type='hidden' name='state' value='{$page_one_values['state']}' />";
  $block_code .= "<input type='hidden' name='zip' value='{$page_one_values['zip_code']}' />";
  $block_code .= "<input type='hidden' name='country' value='US' />";
  $block_code .= "<input type='hidden' name='night_phone_a' value='{$night_phone_a}' />";
  $block_code .= "<input type='hidden' name='night_phone_b' value='{$night_phone_b}' />";
  $block_code .= "<input type='hidden' name='night_phone_c' value='{$night_phone_c}' />";
  $block_code .= "<input type='hidden' name='email' value='{$page_one_values['email']}' />";

  // Add item(s) to cart
  $block_code .= "<input type='hidden' name='item_name_1' value='Registration'>";
  $block_code .= "<input type='hidden' name='amount_1' value='$registration_fee'>";
  $block_code .= "<input type='hidden' name='item_number_1' value='registration'>";
  $block_code .= "<input type='hidden' name='quantity_1' value='1'>";

  if ($donation <> 0) {    
    $block_code .= "<input type='hidden' name='item_name_2' value='Donation'>";
    $block_code .= "<input type='hidden' name='amount_2' value='$donation'>";
    $block_code .= "<input type='hidden' name='item_number_2' value='donation'>";
    $block_code .= "<input type='hidden' name='quantity_2' value='1'>";
  }

  // Add button code
  $block_code .= "<input type='image' name='submit' src='https://www.paypalobjects.com/webstatic/en_US/i/buttons/checkout-logo-large.png' alt='Check out with PayPal'>";
  $block_code .= "</form></div>";

  // Save form to Session
  $_SESSION['paypal_form'] = $block_code;

  // Redirect to paypal payment page
  drupal_goto('content/paypal-payment-page');
}


