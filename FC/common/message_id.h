#ifndef _MESSAGE_ID_H_
#define _MESSAGE_ID_H_
/* how to define a message id ? */
/* 
  we define the message id as a enum start with 0
*/
typedef enum INDEX_BEAN
{   
    INDEX_BEAN_0 = 0, /* never used so if any bean index is 0, that is a invalid bean*/
    INDEX_BEAN_1,
    INDEX_BEAN_2,
    INDEX_BEAN_MAX
}INDEX_BEAN_ENUM;


#endif /* MESSAGE_ID */


