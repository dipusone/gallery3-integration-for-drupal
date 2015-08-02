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

	//Only for debug purpose

	// $form['gallery3_integration_gallery3_groups'] = array(
	// 	'#type' => 'textarea',
	// 	'#title' => t('Gallery3 groups, not editable'),
	// 	'#rows' => count(gallery3_integration_get_gallery3_groups())+1,
	// 	'#default_value' => gallery3_integration_build_groups_textfiled(),
	// 	'#description' => t('This are all the groups presents in the gallery3 db'),
	// 	'#required' => FALSE,
	// 	// '#disabled' => TRUE,


	// );

	$form['gallery3_integration_manage_groups'] = array(
		'#type' => 'checkbox',
		'#title' => t('Manage the roles in Gallery3 from drupal'),
		'#description' => t('Set to let the plugin manage the role CRUD in Gallery3 from drupal.'.
			'<br>This will also enable the role managment per user.'),
		'#default_value' => gallery3_integration_checkbox_default(),
		);
	//Get drupal roles and sort them, this value is used later.
	$drupal_roles = user_roles();
	asort($drupal_roles);

	$form['gallery3_integration_roles'] = array(
		'#type' => 'fieldset',
		'#title' => t('Roles associations'),
		'#description' => t('In this section you will be able associate a Drupal role with the corresponding Gallery role'),
		'#collapsible' => TRUE,
		'#collapsed' => !variable_get('gallery3_integration_manage_groups'),
		);



	foreach ($drupal_roles as $id => $role) {
		//Skip admin and anonimous user and autenticated, this will be added automatically
		if ($id <= 3){
			continue;
		}
		$form['gallery3_integration_roles']['gallery3_integration_role_'.$id] = array(
		'#type' => 'select',
		'#title' => "Associate $role (id = $id) whit gallery3 role",
		'#default_value' => gallery3_integration_select_default($id),
		'#options' => gallery3_integration_get_gallery3_groups(),
		'#description' => 'Select a role in gallery3 for '.$role,
		);
	}


	$form['gallery3_integration_gallery_admin'] = array(
		'#type' => 'fieldset',
		'#title' => t('Gallery3 admin Managment'),
		'#description' => t('In this section you will be able associate a Gallery Administrator with a drupal role.'),
		'#collapsible' => TRUE,
		'#collapsed' => !variable_get('gallery3_integration_manage_admin'),
		);

	$form['gallery3_integration_gallery_admin']['gallery3_integration_manage_admin'] = array(
		'#type' => 'checkbox',
		'#title' => t('Manage admin in gallery'),
		'#description' =>t('Set to let the plugin manage the admin role in Gallery3  from drupal'),
		'#default_value' => gallery3_integration_checkbox_admin_default(),
	);



	$form['gallery3_integration_gallery_admin']['gallery3_integration_admin_role'] = array(
		'#type' => 'select',
		'#title' => "Associate a drupal role whit gallery3 admin",
		'#default_value' => gallery3_integration_select_admin_default(), #should be the admin id.
		'#options' => $drupal_roles,
		'#description' => t('Select a role in drupal for admin in gallery3, this is enabled only if <b><i>Manage admin in gallery</i></b> is selected'),
		'#disabled' => !variable_get('gallery3_integration_manage_admin'),
	);

	return system_settings_form($form);

}

function gallery3_integration_build_groups_textfiled(){
	$groups_string="";
	foreach (gallery3_integration_get_gallery3_groups() as $id => $name) {
		$groups_string .= $name." : ".$id."\n";
	}

	return $groups_string;
}

function gallery3_integration_select_default($id){

	$variable = variable_get('gallery3_integration_role_'.$id);

	if (empty($variable)){
		return 'None';
	}

	return variable_get('gallery3_integration_role_'.$id);
}

function gallery3_integration_checkbox_default(){
	$variable = variable_get('gallery3_integration_manage_groups');

	if(!empty($variable)){
		return TRUE;
	}
	return FALSE;

}

function gallery3_integration_select_admin_default(){
	$variable = variable_get('gallery3_integration_admin_role');
	if (empty($variable)){
		return '3';#Admin role
	}
	return $variable;
}

function gallery3_integration_checkbox_admin_default(){
	$variable = variable_get('gallery3_integration_manage_admin');

	if(!empty($variable)){
		return TRUE;
	}
	return FALSE;


}
