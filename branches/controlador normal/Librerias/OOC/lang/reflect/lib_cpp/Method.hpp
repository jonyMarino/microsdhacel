#ifndef _METHOD_HPP
#define _METHOD_HPP


#pragma DATA_SEG METHOD_DATA                                            
#pragma CODE_SEG METHOD_CODE 
#pragma CONST_SEG DEFAULT



struct Method{
  public:
    typedef void (*pMethod)(void*);
    
   // Method(pMethod method,void * obj);   
    
    void execute(void)const;

    inline pMethod getMethod(void)const{return pmethod;}

    inline void * getObj(void)const {return obj;}; 
  
    pMethod pmethod;
    void* obj;
};


#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 

#endif