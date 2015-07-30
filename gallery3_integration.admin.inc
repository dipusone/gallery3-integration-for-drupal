<?php


function gallery3_integration_admin_form($form, $form_state){
	$form['gallery3_integration_db_prefix'] = array(
		'#type' => 'textfield',
		'#title' => t('Gallery3 tables prefixes'),
		'#size' => 20,
		'#maxlength' => 30,
		'#default_value'=> variable_get('gallery3_integration_db_prefix','g3_'),
		'#description' => t('The prefix of the gallery3 tables in the database.'.
			'Remember to add any underscore!'),
		'#required' => TRUE,

	);
	dprint_r($form);

	return system_settings_form($form);

}

