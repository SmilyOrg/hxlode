#ifndef HX_OBJECT_H
#define HX_OBJECT_H

#ifndef HXCPP_H
#error "Please include hxcpp.h, not hx/Object.h"
#endif




// --- Constants -------------------------------------------------------

enum ObjectType
{
   vtUnknown = -1,
   vtInt = 0xff,
   vtNull = 0,
   vtFloat = 1,
   vtBool = 2,
   vtString = 3,
   vtObject = 4,
   vtArray = 5,
   vtFunction = 6,
   vtEnum,
   vtClass,
   vtAbstractBase = 0x100,
};





namespace hx
{



class FieldRef;
class IndexRef;
typedef Array<Dynamic> DynamicArray;



// --- hx::Object ------------------------------------------------------------
//
// Base for all hxcpp objects.
// This contains the virtual functions required by the core to provide
//  a generic interface to the specific classes.
//
// Hxcpp classes inherit from this.
//
class HXCPP_EXTERN_CLASS_ATTRIBUTES Object
{
public:
   // These allocate the function using the garbage-colleced malloc
   void *operator new( size_t inSize, bool inContainer=true );
   void operator delete( void *, bool ) { }

   //virtual void *__root();
   virtual void __Mark(hx::MarkContext *__inCtx) { }
   #ifdef HXCPP_VISIT_ALLOCS
   virtual void __Visit(hx::VisitContext *__inCtx) { }
   #endif
   virtual bool __Is(hx::Object *inClass) const { return true; }
   virtual hx::Object *__ToInterface(const hx::type_info &inInterface) { return 0; }
   virtual hx::Object *__GetRealObject() { return this; }

   // helpers...
   bool __Is(Dynamic inClass ) const;
   bool __IsArray() const { return __GetType()==vtArray; }

   virtual int __GetType() const { return vtUnknown; }
   virtual void *__GetHandle() const { return 0; }


   virtual hx::FieldRef __FieldRef(const String &inString);

   virtual String __ToString() const;

   virtual int __ToInt() const { return 0; }
   virtual double __ToDouble() const { return 0.0; }
   virtual const char * __CStr() const;
   virtual String toString();
   virtual bool __HasField(const String &inString);
   virtual Dynamic __Field(const String &inString, bool inCallProp);
   virtual Dynamic __IField(int inFieldID);
   virtual double __INumField(int inFieldID);
   virtual Dynamic __SetField(const String &inField,const Dynamic &inValue, bool inCallProp);
   virtual void  __SetThis(Dynamic inThis);
   virtual Dynamic __Run(const Array<Dynamic> &inArgs);
   virtual hx::FieldMap *__GetFieldMap();
   virtual void __GetFields(Array<String> &outFields);
   virtual Class __GetClass() const;

   virtual int __Compare(const hx::Object *inRHS) const;
   virtual DynamicArray __EnumParams();
   virtual String __Tag() const;
   virtual int __Index() const;

   virtual int __length() const { return 0; }
   virtual Dynamic __GetItem(int inIndex) const;
   virtual Dynamic __SetItem(int inIndex,Dynamic inValue);
   virtual void __SetSize(int inLen) { }

   typedef const Dynamic &D;
   virtual Dynamic __run();
   virtual Dynamic __run(D a);
   virtual Dynamic __run(D a,D b);
   virtual Dynamic __run(D a,D b,D c);
   virtual Dynamic __run(D a,D b,D c,D d);
   virtual Dynamic __run(D a,D b,D c,D d,D e);

   virtual int __ArgCount() const { return -1; }

   inline bool __compare( hx::Object *inRHS )
      { return __GetRealObject()!=inRHS->__GetRealObject(); }

   static Class &__SGetClass();
   static void __boot();
};

// --- hx::ObjectPtr ---------------------------------------------------------------
//
// This class simply provides syntax so that pointers can be written as objects,
//  and overloaded operators can be used

template<typename OBJ_>
class ObjectPtr
{
   inline bool SetPtr(OBJ_ *inPtr)
   {
      mPtr = inPtr;
      return true;
   }
   inline bool SetPtr(...) { return false; }

   void CastPtr(hx::Object *inPtr)
   {
      if (inPtr)
      {
         mPtr = dynamic_cast<OBJ_ *>(inPtr->__GetRealObject());
         if (!mPtr)
            mPtr = (Ptr)inPtr->__ToInterface(typeid(Obj));
      }
      else
         mPtr = 0;
   }

public:
   typedef OBJ_ Obj;
   typedef OBJ_ *Ptr;

   ObjectPtr() : mPtr(0) { }
   ObjectPtr(OBJ_ *inObj) : mPtr(inObj) { }
   ObjectPtr(const null &inNull) : mPtr(0) { }
   ObjectPtr(const ObjectPtr<OBJ_> &inOther) : mPtr( inOther.mPtr ) {  }

   template<typename SOURCE_>
   ObjectPtr(const ObjectPtr<SOURCE_> &inObjectPtr)
   {
      if (!SetPtr(inObjectPtr.mPtr))
         CastPtr(inObjectPtr.mPtr);
   }

   template<typename SOURCE_>
   ObjectPtr(const SOURCE_ *inPtr)
   {
      if (!SetPtr(const_cast<SOURCE_ *>(inPtr)))
         CastPtr(const_cast<SOURCE_ *>(inPtr));
   }

   ObjectPtr &operator=(const null &inNull) { mPtr = 0; return *this; }
   ObjectPtr &operator=(Ptr inRHS) { mPtr = inRHS; return *this; }
   ObjectPtr &operator=(const ObjectPtr &inRHS) { mPtr = inRHS.mPtr; return *this; }
   template<typename InterfaceImpl>
   ObjectPtr &operator=(InterfaceImpl *inRHS)
   {
      mPtr = inRHS->operator Ptr();
      return *this;
   }

   inline OBJ_ *GetPtr() const { return mPtr; }
   inline OBJ_ *operator->()
   {
      #ifdef HXCPP_CHECK_POINTER
      if (!mPtr) NullObjectReference();
      #endif
      return mPtr;
   }
   inline const OBJ_ *operator->() const
   {
      #ifdef HXCPP_CHECK_POINTER
      if (!mPtr) NullObjectReference();
      #endif
      return mPtr;
   }

   bool operator==(const ObjectPtr &inRHS) const
   {
      if (mPtr==inRHS.mPtr) return true;
      if (!mPtr || !inRHS.mPtr) return false;
      return !mPtr->__compare(inRHS.mPtr);
   }
   bool operator!=(const ObjectPtr &inRHS) const
   {
      if (mPtr==inRHS.mPtr) return false;
      if (!mPtr || !inRHS.mPtr) return true;
      return mPtr->__compare(inRHS.mPtr);
   }

   bool operator==(const null &inRHS) const { return mPtr==0; }
   bool operator!=(const null &inRHS) const { return mPtr!=0; }

   //inline bool operator==(const Dynamic &inRHS) const { return inRHS==*this; }
   //inline bool operator!=(const Dynamic &inRHS) const { return inRHS!=*this; }


   // This is defined in the "FieldRef" class...
   inline class hx::FieldRef FieldRef(const String &inString);
   inline class hx::IndexRef IndexRef(int inString);
   static Class &__SGetClass() { return OBJ_::__SGetClass(); }

   OBJ_ *mPtr;
};


} // end namespace hx



#endif
