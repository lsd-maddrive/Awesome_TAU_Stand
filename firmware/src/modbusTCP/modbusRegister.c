#include "modbusRegister.h"
#include "stdlib.h"


//Create current analog register
analog_node_t* current_analog=NULL;

//Create current discrete register
discrete_node_t* current_discrete=NULL;

//Create analog Register
analog_node_t* Reg_analog_1=NULL;
analog_node_t* Reg_analog_2=NULL;
analog_node_t* Reg_analog_3=NULL;
analog_node_t* Reg_analog_4=NULL;
analog_node_t* Reg_analog_5=NULL;
analog_node_t* Reg_analog_6=NULL;
analog_node_t* Reg_analog_7=NULL;
analog_node_t* Reg_analog_8=NULL;
analog_node_t* Reg_analog_9=NULL;
analog_node_t* Reg_analog_10=NULL;
analog_node_t* Reg_analog_11=NULL;
analog_node_t* Reg_analog_12=NULL;
analog_node_t* Reg_analog_13=NULL;
analog_node_t* Reg_analog_14=NULL;
analog_node_t* Reg_analog_15=NULL;
analog_node_t* Reg_analog_16=NULL;
analog_node_t* Reg_analog_17=NULL;
analog_node_t* Reg_analog_18=NULL;
analog_node_t* Reg_analog_19=NULL;
analog_node_t* Reg_analog_20=NULL;
analog_node_t* Reg_analog_21=NULL;
analog_node_t* Reg_analog_22=NULL;
analog_node_t* Reg_analog_23=NULL;
analog_node_t* Reg_analog_24=NULL;
analog_node_t* Reg_analog_25=NULL;
analog_node_t* Reg_analog_26=NULL;
analog_node_t* Reg_analog_27=NULL;
analog_node_t* Reg_analog_28=NULL;
analog_node_t* Reg_analog_29=NULL;
analog_node_t* Reg_analog_30=NULL;
analog_node_t* Reg_analog_31=NULL;
analog_node_t* Reg_analog_32=NULL;
analog_node_t* Reg_analog_33=NULL;
analog_node_t* Reg_analog_34=NULL;
analog_node_t* Reg_analog_35=NULL;
analog_node_t* Reg_analog_36=NULL;
analog_node_t* Reg_analog_37=NULL;
analog_node_t* Reg_analog_38=NULL;
analog_node_t* Reg_analog_39=NULL;
analog_node_t* Reg_analog_40=NULL;
analog_node_t* Reg_analog_41=NULL;
analog_node_t* Reg_analog_42=NULL;
analog_node_t* Reg_analog_43=NULL;
analog_node_t* Reg_analog_44=NULL;
analog_node_t* Reg_analog_45=NULL;
analog_node_t* Reg_analog_46=NULL;
analog_node_t* Reg_analog_47=NULL;
analog_node_t* Reg_analog_48=NULL;
analog_node_t* Reg_analog_49=NULL;
analog_node_t* Reg_analog_50=NULL;

//Create discrete Register
discrete_node_t* Reg_discrete_1=NULL;
discrete_node_t* Reg_discrete_2=NULL;
discrete_node_t* Reg_discrete_3=NULL;
discrete_node_t* Reg_discrete_4=NULL;
discrete_node_t* Reg_discrete_5=NULL;
discrete_node_t* Reg_discrete_6=NULL;
discrete_node_t* Reg_discrete_7=NULL;
discrete_node_t* Reg_discrete_8=NULL;
discrete_node_t* Reg_discrete_9=NULL;
discrete_node_t* Reg_discrete_10=NULL;
discrete_node_t* Reg_discrete_11=NULL;
discrete_node_t* Reg_discrete_12=NULL;
discrete_node_t* Reg_discrete_13=NULL;
discrete_node_t* Reg_discrete_14=NULL;
discrete_node_t* Reg_discrete_15=NULL;
discrete_node_t* Reg_discrete_16=NULL;
discrete_node_t* Reg_discrete_17=NULL;
discrete_node_t* Reg_discrete_18=NULL;
discrete_node_t* Reg_discrete_19=NULL;
discrete_node_t* Reg_discrete_20=NULL;
discrete_node_t* Reg_discrete_21=NULL;
discrete_node_t* Reg_discrete_22=NULL;
discrete_node_t* Reg_discrete_23=NULL;
discrete_node_t* Reg_discrete_24=NULL;
discrete_node_t* Reg_discrete_25=NULL;
discrete_node_t* Reg_discrete_26=NULL;
discrete_node_t* Reg_discrete_27=NULL;
discrete_node_t* Reg_discrete_28=NULL;
discrete_node_t* Reg_discrete_29=NULL;
discrete_node_t* Reg_discrete_30=NULL;
discrete_node_t* Reg_discrete_31=NULL;
discrete_node_t* Reg_discrete_32=NULL;
discrete_node_t* Reg_discrete_33=NULL;
discrete_node_t* Reg_discrete_34=NULL;
discrete_node_t* Reg_discrete_35=NULL;
discrete_node_t* Reg_discrete_36=NULL;
discrete_node_t* Reg_discrete_37=NULL;
discrete_node_t* Reg_discrete_38=NULL;
discrete_node_t* Reg_discrete_39=NULL;
discrete_node_t* Reg_discrete_40=NULL;
discrete_node_t* Reg_discrete_41=NULL;
discrete_node_t* Reg_discrete_42=NULL;
discrete_node_t* Reg_discrete_43=NULL;
discrete_node_t* Reg_discrete_44=NULL;
discrete_node_t* Reg_discrete_45=NULL;
discrete_node_t* Reg_discrete_46=NULL;
discrete_node_t* Reg_discrete_47=NULL;
discrete_node_t* Reg_discrete_48=NULL;
discrete_node_t* Reg_discrete_49=NULL;
discrete_node_t* Reg_discrete_50=NULL;

void modbus_register_create(void)
{
   modbus_analog_register_create(); 
   modbus_discrete_register_create();
   current_analog=Reg_analog_1;
   current_discrete=Reg_discrete_1;
}

void modbus_discrete_register_create(void)
{
   //Create discrete Register 1
   Reg_discrete_1=malloc(sizeof(discrete_node_t));
   Reg_discrete_1->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_1->value=1;
   Reg_discrete_1->address=0;
   //Create discrete Register 2
   Reg_discrete_2=Reg_discrete_1->next;
   Reg_discrete_2->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_2->value=0;
   Reg_discrete_2->address=1;
   //Create discrete Register 3
   Reg_discrete_3=Reg_discrete_2->next;
   Reg_discrete_3->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_3->value=1;
   Reg_discrete_3->address=2;
   //Create discrete Register 4
   Reg_discrete_4=Reg_discrete_3->next;
   Reg_discrete_4->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_4->value=0;
   Reg_discrete_4->address=3;
   //Create discrete Register 5
   Reg_discrete_5=Reg_discrete_4->next;
   Reg_discrete_5->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_5->value=0;
   Reg_discrete_5->address=4;
   //Create discrete Register 6
   Reg_discrete_6=Reg_discrete_5->next;
   Reg_discrete_6->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_6->value=1;
   Reg_discrete_6->address=5;
   //Create discrete Register 7
   Reg_discrete_7=Reg_discrete_6->next;
   Reg_discrete_7->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_7->value=0;
   Reg_discrete_7->address=6;
   //Create discrete Register 8
   Reg_discrete_8=Reg_discrete_7->next;
   Reg_discrete_8->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_8->value=0;
   Reg_discrete_8->address=7;   
   //Create discrete Register 9
   Reg_discrete_9=Reg_discrete_8->next;
   Reg_discrete_9->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_9->value=1;
   Reg_discrete_9->address=8; 
   //Create discrete Register 10
   Reg_discrete_10=Reg_discrete_9->next;
   Reg_discrete_10->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_10->value=0;
   Reg_discrete_10->address=9;  
   //Create discrete Register 11
   Reg_discrete_11=Reg_discrete_10->next;
   Reg_discrete_11->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_11->value=0;
   Reg_discrete_11->address=10;   
   //Create discrete Register 12
   Reg_discrete_12=Reg_discrete_11->next;
   Reg_discrete_12->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_12->value=0;
   Reg_discrete_12->address=11;  
   //Create discrete Register 13
   Reg_discrete_13=Reg_discrete_12->next;
   Reg_discrete_13->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_13->value=0;
   Reg_discrete_13->address=12;  
   //Create discrete Register 14
   Reg_discrete_14=Reg_discrete_13->next;
   Reg_discrete_14->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_14->value=0;
   Reg_discrete_14->address=13; 
   //Create discrete Register 15
   Reg_discrete_15=Reg_discrete_14->next;
   Reg_discrete_15->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_15->value=0;
   Reg_discrete_15->address=14;   
   //Create discrete Register 16
   Reg_discrete_16=Reg_discrete_15->next;
   Reg_discrete_16->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_16->value=0;
   Reg_discrete_16->address=15;
   //Create discrete Register 17
   Reg_discrete_17=Reg_discrete_16->next;
   Reg_discrete_17->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_17->value=0;
   Reg_discrete_17->address=16;
   //Create discrete Register 18
   Reg_discrete_18=Reg_discrete_17->next;
   Reg_discrete_18->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_18->value=0;
   Reg_discrete_18->address=17;   
   //Create discrete Register 19
   Reg_discrete_19=Reg_discrete_18->next;
   Reg_discrete_19->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_19->value=0;
   Reg_discrete_19->address=18; 
   //Create discrete Register 20
   Reg_discrete_20=Reg_discrete_19->next;
   Reg_discrete_20->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_20->value=0;
   Reg_discrete_20->address=19; 
   //Create discrete Register 21
   Reg_discrete_21=Reg_discrete_20->next;
   Reg_discrete_21->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_21->value=0;
   Reg_discrete_21->address=20;
   //Create discrete Register 22
   Reg_discrete_22=Reg_discrete_21->next;
   Reg_discrete_22->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_22->value=0;
   Reg_discrete_22->address=21;
   //Create discrete Register 23
   Reg_discrete_23=Reg_discrete_22->next;
   Reg_discrete_23->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_23->value=0;
   Reg_discrete_23->address=22;
   //Create discrete Register 24
   Reg_discrete_24=Reg_discrete_23->next;
   Reg_discrete_24->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_24->value=0;
   Reg_discrete_24->address=23;
   //Create discrete Register 25
   Reg_discrete_25=Reg_discrete_24->next;
   Reg_discrete_25->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_25->value=0;
   Reg_discrete_25->address=24;
   //Create discrete Register 26
   Reg_discrete_26=Reg_discrete_25->next;
   Reg_discrete_26->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_26->value=0;
   Reg_discrete_26->address=25;
   //Create discrete Register 27
   Reg_discrete_27=Reg_discrete_26->next;
   Reg_discrete_27->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_27->value=0;
   Reg_discrete_27->address=26;
   //Create discrete Register 28
   Reg_discrete_28=Reg_discrete_27->next;
   Reg_discrete_28->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_28->value=0;
   Reg_discrete_28->address=27;
   //Create discrete Register 29
   Reg_discrete_29=Reg_discrete_28->next;
   Reg_discrete_29->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_29->value=0;
   Reg_discrete_29->address=28;
   //Create discreteRegister 30
   Reg_discrete_30=Reg_discrete_29->next;
   Reg_discrete_30->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_30->value=0;
   Reg_discrete_30->address=29;
   //Create discrete Register 31
   Reg_discrete_31=Reg_discrete_30->next;
   Reg_discrete_31->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_31->value=0;
   Reg_discrete_31->address=30;
   //Create discrete Register 32
   Reg_discrete_32=Reg_discrete_31->next;
   Reg_discrete_32->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_32->value=0;
   Reg_discrete_32->address=31;
   //Create discrete Register 33
   Reg_discrete_33=Reg_discrete_32->next;
   Reg_discrete_33->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_33->value=0;
   Reg_discrete_33->address=32;
   //Create discrete Register 34
   Reg_discrete_34=Reg_discrete_33->next;
   Reg_discrete_34->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_34->value=0;
   Reg_discrete_34->address=33;
   //Create discrete Register 35
   Reg_discrete_35=Reg_discrete_34->next;
   Reg_discrete_35->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_35->value=0;
   Reg_discrete_35->address=34;
   //Create discrete Register 36
   Reg_discrete_36=Reg_discrete_35->next;
   Reg_discrete_36->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_36->value=0;
   Reg_discrete_36->address=35;
   //Create discrete Register 37
   Reg_discrete_37=Reg_discrete_36->next;
   Reg_discrete_37->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_37->value=0;
   Reg_discrete_37->address=36;
   //Create discrete Register 38
   Reg_discrete_38=Reg_discrete_37->next;
   Reg_discrete_38->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_38->value=0;
   Reg_discrete_38->address=37;
   //Create discrete Register 39
   Reg_discrete_39=Reg_discrete_38->next;
   Reg_discrete_39->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_39->value=0;
   Reg_discrete_39->address=38;
   //Create discrete Register 40
   Reg_discrete_40=Reg_discrete_39->next;
   Reg_discrete_40->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_40->value=1;
   Reg_discrete_40->address=39;
   //Create discrete Register 41
   Reg_discrete_41=Reg_discrete_40->next;
   Reg_discrete_41->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_41->value=0;
   Reg_discrete_41->address=40;
   //Create discrete Register 42
   Reg_discrete_42=Reg_discrete_41->next;
   Reg_discrete_42->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_42->value=1;
   Reg_discrete_42->address=41;
   //Create discrete Register 43
   Reg_discrete_43=Reg_discrete_42->next;
   Reg_discrete_43->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_43->value=0;
   Reg_discrete_43->address=42;
   //Create discrete Register 44
   Reg_discrete_44=Reg_discrete_43->next;
   Reg_discrete_44->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_44->value=1;
   Reg_discrete_44->address=43;
   //Create discrete Register 45
   Reg_discrete_45=Reg_discrete_44->next;
   Reg_discrete_45->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_45->value=0;
   Reg_discrete_45->address=44;
   //Create discrete Register 46
   Reg_discrete_46=Reg_discrete_45->next;
   Reg_discrete_46->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_46->value=1;
   Reg_discrete_46->address=45;
   //Create discrete Register 47
   Reg_discrete_47=Reg_discrete_46->next;
   Reg_discrete_47->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_47->value=0;
   Reg_discrete_47->address=46;
   //Create discrete Register 48
   Reg_discrete_48=Reg_discrete_47->next;
   Reg_discrete_48->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_48->value=0;
   Reg_discrete_48->address=47;
   //Create discrete Register 49
   Reg_discrete_49=Reg_discrete_48->next;
   Reg_discrete_49->next=malloc(sizeof(discrete_node_t));
   Reg_discrete_49->value=0;
   Reg_discrete_49->address=48;
   //Create discrete Register 50
   Reg_discrete_50=Reg_discrete_49->next;
   Reg_discrete_50->next=NULL;
   Reg_discrete_50->value=1;
   Reg_discrete_50->address=49;
	
}

void modbus_analog_register_create(void)
{
   //Create analog Register 1
   Reg_analog_1=malloc(sizeof(analog_node_t));
   Reg_analog_1->next=malloc(sizeof(analog_node_t));
   Reg_analog_1->value=888;
   Reg_analog_1->address=0;
   //Create analog Register 2
   Reg_analog_2=Reg_analog_1->next;
   Reg_analog_2->next=malloc(sizeof(analog_node_t));
   Reg_analog_2->value=77;
   Reg_analog_2->address=1;
   //Create analog Register 3
   Reg_analog_3=Reg_analog_2->next;
   Reg_analog_3->next=malloc(sizeof(analog_node_t));
   Reg_analog_3->value=555;
   Reg_analog_3->address=2;
   //Create analog Register 4
   Reg_analog_4=Reg_analog_3->next;
   Reg_analog_4->next=malloc(sizeof(analog_node_t));
   Reg_analog_4->value=0;
   Reg_analog_4->address=3;
   //Create analog Register 5
   Reg_analog_5=Reg_analog_4->next;
   Reg_analog_5->next=malloc(sizeof(analog_node_t));
   Reg_analog_5->value=0;
   Reg_analog_5->address=4;
   //Create analog Register 6
   Reg_analog_6=Reg_analog_5->next;
   Reg_analog_6->next=malloc(sizeof(analog_node_t));
   Reg_analog_6->value=0;
   Reg_analog_6->address=5;
   //Create analog Register 7
   Reg_analog_7=Reg_analog_6->next;
   Reg_analog_7->next=malloc(sizeof(analog_node_t));
   Reg_analog_7->value=0;
   Reg_analog_7->address=6;
   //Create analog Register 8
   Reg_analog_8=Reg_analog_7->next;
   Reg_analog_8->next=malloc(sizeof(analog_node_t));
   Reg_analog_8->value=0;
   Reg_analog_8->address=7;   
   //Create analog Register 9
   Reg_analog_9=Reg_analog_8->next;
   Reg_analog_9->next=malloc(sizeof(analog_node_t));
   Reg_analog_9->value=0;
   Reg_analog_9->address=8; 
   //Create analog Register 10
   Reg_analog_10=Reg_analog_9->next;
   Reg_analog_10->next=malloc(sizeof(analog_node_t));
   Reg_analog_10->value=0;
   Reg_analog_10->address=9;  
   //Create analog Register 11
   Reg_analog_11=Reg_analog_10->next;
   Reg_analog_11->next=malloc(sizeof(analog_node_t));
   Reg_analog_11->value=0;
   Reg_analog_11->address=10;   
   //Create analog Register 12
   Reg_analog_12=Reg_analog_11->next;
   Reg_analog_12->next=malloc(sizeof(analog_node_t));
   Reg_analog_12->value=0;
   Reg_analog_12->address=11;  
   //Create analog Register 13
   Reg_analog_13=Reg_analog_12->next;
   Reg_analog_13->next=malloc(sizeof(analog_node_t));
   Reg_analog_13->value=0;
   Reg_analog_13->address=12;  
   //Create analog Register 14
   Reg_analog_14=Reg_analog_13->next;
   Reg_analog_14->next=malloc(sizeof(analog_node_t));
   Reg_analog_14->value=0;
   Reg_analog_14->address=13; 
   //Create analog Register 15
   Reg_analog_15=Reg_analog_14->next;
   Reg_analog_15->next=malloc(sizeof(analog_node_t));
   Reg_analog_15->value=0;
   Reg_analog_15->address=14;   
   //Create analog Register 16
   Reg_analog_16=Reg_analog_15->next;
   Reg_analog_16->next=malloc(sizeof(analog_node_t));
   Reg_analog_16->value=0;
   Reg_analog_16->address=15;
   //Create analog Register 17
   Reg_analog_17=Reg_analog_16->next;
   Reg_analog_17->next=malloc(sizeof(analog_node_t));
   Reg_analog_17->value=0;
   Reg_analog_17->address=16;
   //Create analog Register 18
   Reg_analog_18=Reg_analog_17->next;
   Reg_analog_18->next=malloc(sizeof(analog_node_t));
   Reg_analog_18->value=0;
   Reg_analog_18->address=17;   
   //Create analog Register 19
   Reg_analog_19=Reg_analog_18->next;
   Reg_analog_19->next=malloc(sizeof(analog_node_t));
   Reg_analog_19->value=0;
   Reg_analog_19->address=18; 
   //Create analog Register 20
   Reg_analog_20=Reg_analog_19->next;
   Reg_analog_20->next=malloc(sizeof(analog_node_t));
   Reg_analog_20->value=0;
   Reg_analog_20->address=19; 
   //Create analog Register 21
   Reg_analog_21=Reg_analog_20->next;
   Reg_analog_21->next=malloc(sizeof(analog_node_t));
   Reg_analog_21->value=0;
   Reg_analog_21->address=20;
   //Create analog Register 22
   Reg_analog_22=Reg_analog_21->next;
   Reg_analog_22->next=malloc(sizeof(analog_node_t));
   Reg_analog_22->value=0;
   Reg_analog_22->address=21;
   //Create analog Register 23
   Reg_analog_23=Reg_analog_22->next;
   Reg_analog_23->next=malloc(sizeof(analog_node_t));
   Reg_analog_23->value=0;
   Reg_analog_23->address=22;
   //Create analog Register 24
   Reg_analog_24=Reg_analog_23->next;
   Reg_analog_24->next=malloc(sizeof(analog_node_t));
   Reg_analog_24->value=0;
   Reg_analog_24->address=23;
   //Create analog Register 25
   Reg_analog_25=Reg_analog_24->next;
   Reg_analog_25->next=malloc(sizeof(analog_node_t));
   Reg_analog_25->value=0;
   Reg_analog_25->address=24;
   //Create analog Register 26
   Reg_analog_26=Reg_analog_25->next;
   Reg_analog_26->next=malloc(sizeof(analog_node_t));
   Reg_analog_26->value=0;
   Reg_analog_26->address=25;
   //Create analog Register 27
   Reg_analog_27=Reg_analog_26->next;
   Reg_analog_27->next=malloc(sizeof(analog_node_t));
   Reg_analog_27->value=0;
   Reg_analog_27->address=26;
   //Create analog Register 28
   Reg_analog_28=Reg_analog_27->next;
   Reg_analog_28->next=malloc(sizeof(analog_node_t));
   Reg_analog_28->value=0;
   Reg_analog_28->address=27;
   //Create analog Register 29
   Reg_analog_29=Reg_analog_28->next;
   Reg_analog_29->next=malloc(sizeof(analog_node_t));
   Reg_analog_29->value=0;
   Reg_analog_29->address=28;
   //Create analog Register 30
   Reg_analog_30=Reg_analog_29->next;
   Reg_analog_30->next=malloc(sizeof(analog_node_t));
   Reg_analog_30->value=0;
   Reg_analog_30->address=29;
   //Create analog Register 31
   Reg_analog_31=Reg_analog_30->next;
   Reg_analog_31->next=malloc(sizeof(analog_node_t));
   Reg_analog_31->value=0;
   Reg_analog_31->address=30;
   //Create analog Register 32
   Reg_analog_32=Reg_analog_31->next;
   Reg_analog_32->next=malloc(sizeof(analog_node_t));
   Reg_analog_32->value=0;
   Reg_analog_32->address=31;
   //Create analog Register 33
   Reg_analog_33=Reg_analog_32->next;
   Reg_analog_33->next=malloc(sizeof(analog_node_t));
   Reg_analog_33->value=0;
   Reg_analog_33->address=32;
   //Create analog Register 34
   Reg_analog_34=Reg_analog_33->next;
   Reg_analog_34->next=malloc(sizeof(analog_node_t));
   Reg_analog_34->value=0;
   Reg_analog_34->address=33;
   //Create analog Register 35
   Reg_analog_35=Reg_analog_34->next;
   Reg_analog_35->next=malloc(sizeof(analog_node_t));
   Reg_analog_35->value=0;
   Reg_analog_35->address=34;
   //Create analog Register 36
   Reg_analog_36=Reg_analog_35->next;
   Reg_analog_36->next=malloc(sizeof(analog_node_t));
   Reg_analog_36->value=0;
   Reg_analog_36->address=35;
   //Create analog Register 37
   Reg_analog_37=Reg_analog_36->next;
   Reg_analog_37->next=malloc(sizeof(analog_node_t));
   Reg_analog_37->value=0;
   Reg_analog_37->address=36;
   //Create analog Register 38
   Reg_analog_38=Reg_analog_37->next;
   Reg_analog_38->next=malloc(sizeof(analog_node_t));
   Reg_analog_38->value=0;
   Reg_analog_38->address=37;
   //Create analog Register 39
   Reg_analog_39=Reg_analog_38->next;
   Reg_analog_39->next=malloc(sizeof(analog_node_t));
   Reg_analog_39->value=0;
   Reg_analog_39->address=38;
   //Create analog Register 40
   Reg_analog_40=Reg_analog_39->next;
   Reg_analog_40->next=malloc(sizeof(analog_node_t));
   Reg_analog_40->value=0;
   Reg_analog_40->address=39;
   //Create analog Register 41
   Reg_analog_41=Reg_analog_40->next;
   Reg_analog_41->next=malloc(sizeof(analog_node_t));
   Reg_analog_41->value=0;
   Reg_analog_41->address=40;
   //Create analog Register 42
   Reg_analog_42=Reg_analog_41->next;
   Reg_analog_42->next=malloc(sizeof(analog_node_t));
   Reg_analog_42->value=0;
   Reg_analog_42->address=41;
   //Create analog Register 43
   Reg_analog_43=Reg_analog_42->next;
   Reg_analog_43->next=malloc(sizeof(analog_node_t));
   Reg_analog_43->value=0;
   Reg_analog_43->address=42;
   //Create analog Register 44
   Reg_analog_44=Reg_analog_43->next;
   Reg_analog_44->next=malloc(sizeof(analog_node_t));
   Reg_analog_44->value=0;
   Reg_analog_44->address=43;
   //Create analog Register 45
   Reg_analog_45=Reg_analog_44->next;
   Reg_analog_45->next=malloc(sizeof(analog_node_t));
   Reg_analog_45->value=0;
   Reg_analog_45->address=44;
   //Create analog Register 46
   Reg_analog_46=Reg_analog_45->next;
   Reg_analog_46->next=malloc(sizeof(analog_node_t));
   Reg_analog_46->value=0;
   Reg_analog_46->address=45;
   //Create analog Register 47
   Reg_analog_47=Reg_analog_46->next;
   Reg_analog_47->next=malloc(sizeof(analog_node_t));
   Reg_analog_47->value=0;
   Reg_analog_47->address=46;
   //Create analog Register 48
   Reg_analog_48=Reg_analog_47->next;
   Reg_analog_48->next=malloc(sizeof(analog_node_t));
   Reg_analog_48->value=0;
   Reg_analog_48->address=47;
   //Create analog Register 49
   Reg_analog_49=Reg_analog_48->next;
   Reg_analog_49->next=malloc(sizeof(analog_node_t));
   Reg_analog_49->value=0;
   Reg_analog_49->address=48;
   //Create analog Register 50
   Reg_analog_50=Reg_analog_49->next;
   Reg_analog_50->next=NULL;
   Reg_analog_50->value=0;
   Reg_analog_50->address=49;
}
