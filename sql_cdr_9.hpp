#ifndef SQL_CDR_9_1346942183
#define SQL_CDR_9_1346942183

namespace cdr_oracle_loader
{
    char const sql_cdr_9[] =
        "insert into cdr_format_9 ("

        "hdcd_record_format"
        ", hdcd_cdr_received_from"
        ", recc_cdr_number"
        ", recc_tts_server"
        ", date_creation"
        ", version_number"
        ", ticket_type"
        ", interface_type"
        ", operator_id"
        ", request_id"
        ", activity_cause"
        ", activity_type"
        ", activity_result"
        ", msisdn"
        ", other_msisdn"
        ", location_code_area"
        ", location_cell_id"
        ", location_number"
        ", account_balance"
        ", currency_code"
        ", counters_data"
        ", validity_and_date"
        ", account_event_flags"
        ", reserved"
        ", balance_delta"
        ", voucher_pin"
        ", voucher_sn"
        ", tariff_plan_id"
        ", new_tariff_plan_id"
        ", service_code"
        ", service_start_date"
        ", service_end_date"
        ", ff_number"
        ", ff_position"
        ", fa_destination_index"
        ", fa_time_period_index"
        ", hh_time_period_index"
        ", cug_id"
        ", new_validity_end_date"
        ", language_code"
        ", redemption_code"
        ", gift_quantity"
        ", bonus_balance"
        ", bonus_validity_end_date"
        ", bonus_delta"
        ", admin_lock"
        ", customer_type_id"
        ", billing_group_id"
        ", personal_account_id"
        ", one_time_service_id"
        ", price"
        ", discount"
        ", discount_id"
        ", tax"
        ", tax_percent"
        ", tax_recapitulation_id"
        ", service_provider_id"
        ", unit_price"
        ", number_of_units"
        ", sfbr_type"
        ", metric_unit_number"
        ", procedure_reference"
        ", buffer"

        ") values ("

        ":hdcd_record_format<unsigned>"
        ", :hdcd_cdr_received_from<unsigned>"
        ", :recc_cdr_number<unsigned>"
        ", :recc_tts_server<unsigned>"
        ", :date_creation<timestamp>"
        ", :version_number<unsigned>"
        ", :ticket_type<unsigned>"
        ", :interface_type<unsigned>"
        ", :operator_id<char[11]>"
        ", :request_id<char[11]>"
        ", :activity_cause<unsigned>"
        ", :activity_type<unsigned>"
        ", :activity_result<unsigned>"
        ", :msisdn<char[41]>"
        ", :other_msisdn<char[41]>"
        ", :location_code_area<unsigned>"
        ", :location_cell_id<unsigned>"
        ", :location_number<char[9]>"
        ", :account_balance<bigint>"
        ", :currency_code<unsigned>"
        ", :counters_data<char[151]>"
        ", :validity_and_date<timestamp>"
        ", :account_event_flags<unsigned>"
        ", :reserved<unsigned>"
        ", :balance_delta<bigint>"
        ", :voucher_pin<char[21]>"
        ", :voucher_sn<char[21]>"
        ", :tariff_plan_id<unsigned>"
        ", :new_tariff_plan_id<unsigned>"
        ", :service_code<char[9]>"
        ", :service_start_date<timestamp>"
        ", :service_end_date<timestamp>"
        ", :ff_number<char[13]>"
        ", :ff_position<unsigned>"
        ", :fa_destination_index<unsigned>"
        ", :fa_time_period_index<unsigned>"
        ", :hh_time_period_index<unsigned>"
        ", :cug_id<char[11]>"
        ", :new_validity_end_date<timestamp>"
        ", :language_code<unsigned>"
        ", :redemption_code<char[9]>"
        ", :gift_quantity<unsigned>"
        ", :bonus_balance<unsigned>"
        ", :bonus_validity_end_date<timestamp>"
        ", :bonus_delta<unsigned>"
        ", :admin_lock<unsigned>"
        ", :customer_type_id<unsigned>"
        ", :billing_group_id<unsigned>"
        ", :personal_account_id<bigint>"
        ", :one_time_service_id<unsigned>"
        ", :price<bigint>"
        ", :discount<bigint>"
        ", :discount_id<unsigned>"
        ", :tax<bigint>"
        ", :tax_percent<unsigned>"
        ", :tax_recapitulation_id<unsigned>"
        ", :service_provider_id<unsigned>"
        ", :unit_price<bigint>"
        ", :number_of_units<unsigned>"
        ", :sfbr_type<char[6]>"
        ", :metric_unit_number<unsigned>"
        ", :procedure_reference<bigint>"
        ", :buffer<raw[512]>"
        ")";
}

#endif // SQL_CDR_9_1346942183
