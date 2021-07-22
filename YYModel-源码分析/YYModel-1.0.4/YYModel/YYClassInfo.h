//
//  YYClassInfo.h
//  YYModel <https://github.com/ibireme/YYModel>
//
//  Created by ibireme on 15/5/9.
//  Copyright (c) 2015 ibireme.
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//  定义YYClassInfo类，其中包括了一个方法YYEncodingGetType和4个类

#import <Foundation/Foundation.h>
#import <objc/runtime.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Type encoding's type. 编码类型
 */
typedef NS_OPTIONS(NSUInteger, YYEncodingType) {
    YYEncodingTypeMask       = 0xFF, ///< mask of type value
    YYEncodingTypeUnknown    = 0, ///< unknown
    YYEncodingTypeVoid       = 1, ///< void
    YYEncodingTypeBool       = 2, ///< bool
    YYEncodingTypeInt8       = 3, ///< char / BOOL
    YYEncodingTypeUInt8      = 4, ///< unsigned char
    YYEncodingTypeInt16      = 5, ///< short
    YYEncodingTypeUInt16     = 6, ///< unsigned short
    YYEncodingTypeInt32      = 7, ///< int
    YYEncodingTypeUInt32     = 8, ///< unsigned int
    YYEncodingTypeInt64      = 9, ///< long long
    YYEncodingTypeUInt64     = 10, ///< unsigned long long
    YYEncodingTypeFloat      = 11, ///< float
    YYEncodingTypeDouble     = 12, ///< double
    YYEncodingTypeLongDouble = 13, ///< long double
    YYEncodingTypeObject     = 14, ///< id
    YYEncodingTypeClass      = 15, ///< Class
    YYEncodingTypeSEL        = 16, ///< SEL
    YYEncodingTypeBlock      = 17, ///< block
    YYEncodingTypePointer    = 18, ///< void*
    YYEncodingTypeStruct     = 19, ///< struct
    YYEncodingTypeUnion      = 20, ///< union
    YYEncodingTypeCString    = 21, ///< char*
    YYEncodingTypeCArray     = 22, ///< char[10] (for example)
    
    YYEncodingTypeQualifierMask   = 0xFF00,   ///< mask of qualifier
    YYEncodingTypeQualifierConst  = 1 << 8,  ///< const
    YYEncodingTypeQualifierIn     = 1 << 9,  ///< in
    YYEncodingTypeQualifierInout  = 1 << 10, ///< inout
    YYEncodingTypeQualifierOut    = 1 << 11, ///< out
    YYEncodingTypeQualifierBycopy = 1 << 12, ///< bycopy
    YYEncodingTypeQualifierByref  = 1 << 13, ///< byref
    YYEncodingTypeQualifierOneway = 1 << 14, ///< oneway
    
    YYEncodingTypePropertyMask         = 0xFF0000, ///< mask of property
    YYEncodingTypePropertyReadonly     = 1 << 16, ///< readonly
    YYEncodingTypePropertyCopy         = 1 << 17, ///< copy
    YYEncodingTypePropertyRetain       = 1 << 18, ///< retain
    YYEncodingTypePropertyNonatomic    = 1 << 19, ///< nonatomic
    YYEncodingTypePropertyWeak         = 1 << 20, ///< weak
    YYEncodingTypePropertyCustomGetter = 1 << 21, ///< getter=
    YYEncodingTypePropertyCustomSetter = 1 << 22, ///< setter=
    YYEncodingTypePropertyDynamic      = 1 << 23, ///< @dynamic
};

/** 自定义实例变量Ivar类型
 Get the type from a Type-Encoding string.
 
 @discussion See also:
 https://developer.apple.com/library/mac/documentation/Cocoa/Conceptual/ObjCRuntimeGuide/Articles/ocrtTypeEncodings.html
 https://developer.apple.com/library/mac/documentation/Cocoa/Conceptual/ObjCRuntimeGuide/Articles/ocrtPropertyIntrospection.html
 
 @param typeEncoding  A Type-Encoding string.
 @return The encoding type.
 */
YYEncodingType YYEncodingGetType(const char *typeEncoding);


/**
 Instance variable information. 实例变量的类
 */
@interface YYClassIvarInfo : NSObject
@property (nonatomic, assign, readonly) Ivar ivar;              ///< ivar opaque struct Ivar类型的结构体
@property (nonatomic, strong, readonly) NSString *name;         ///< Ivar's name 名称
@property (nonatomic, assign, readonly) ptrdiff_t offset;       ///< Ivar's offset 偏移量
@property (nonatomic, strong, readonly) NSString *typeEncoding; ///< Ivar's type encoding 类型编码
@property (nonatomic, assign, readonly) YYEncodingType type;    ///< Ivar's type 编码类型

/**
 Creates and returns an ivar info object.
 
 @param ivar ivar opaque struct
 @return A new object, or nil if an error occurs.
 */
- (instancetype)initWithIvar:(Ivar)ivar;
@end


/**
 Method information. 方法类
 */
@interface YYClassMethodInfo : NSObject
@property (nonatomic, assign, readonly) Method method;                  ///< method opaque struct 方法结构体
@property (nonatomic, strong, readonly) NSString *name;                 ///< method name 方法名称
@property (nonatomic, assign, readonly) SEL sel;                        ///< method's selector 方法选择器
@property (nonatomic, assign, readonly) IMP imp;                        ///< method's implementation 方法实现
@property (nonatomic, strong, readonly) NSString *typeEncoding;         ///< method's parameter and return types 方法的类型编码
@property (nonatomic, strong, readonly) NSString *returnTypeEncoding;   ///< return value's type 返回值的类型编码
@property (nullable, nonatomic, strong, readonly) NSArray<NSString *> *argumentTypeEncodings; ///< array of arguments' type 存放参数的类型

/**
 Creates and returns a method info object.
 
 @param method method opaque struct
 @return A new object, or nil if an error occurs.
 */
- (instancetype)initWithMethod:(Method)method;
@end


/**
 Property information. 属性信息类
 */
@interface YYClassPropertyInfo : NSObject
@property (nonatomic, assign, readonly) objc_property_t property; ///< property's opaque struct 属性结构体
@property (nonatomic, strong, readonly) NSString *name;           ///< property's name 属性名称
@property (nonatomic, assign, readonly) YYEncodingType type;      ///< property's type 属性类型
@property (nonatomic, strong, readonly) NSString *typeEncoding;   ///< property's encoding value 属性编码类型
@property (nonatomic, strong, readonly) NSString *ivarName;       ///< property's ivar name 实例变量名称
@property (nullable, nonatomic, assign, readonly) Class cls;      ///< may be nil 类
@property (nullable, nonatomic, strong, readonly) NSArray<NSString *> *protocols; ///< may nil 存放协议的数据
@property (nonatomic, assign, readonly) SEL getter;               ///< getter (nonnull)
@property (nonatomic, assign, readonly) SEL setter;               ///< setter (nonnull)

/**
 Creates and returns a property info object.
 
 @param property property opaque struct
 @return A new object, or nil if an error occurs.
 */
- (instancetype)initWithProperty:(objc_property_t)property;
@end


/**
 Class information for a class. 类信息
 */
@interface YYClassInfo : NSObject
@property (nonatomic, assign, readonly) Class cls; ///< class object 类
@property (nullable, nonatomic, assign, readonly) Class superCls; ///< super class object 父类
@property (nullable, nonatomic, assign, readonly) Class metaCls;  ///< class's meta class object 元类
@property (nonatomic, readonly) BOOL isMeta; ///< whether this class is meta class 是否是元类
@property (nonatomic, strong, readonly) NSString *name; ///< class name 类名称
@property (nullable, nonatomic, strong, readonly) YYClassInfo *superClassInfo; ///< super class's class info 父类信息
@property (nullable, nonatomic, strong, readonly) NSDictionary<NSString *, YYClassIvarInfo *> *ivarInfos; ///< ivars 实例变量信息
@property (nullable, nonatomic, strong, readonly) NSDictionary<NSString *, YYClassMethodInfo *> *methodInfos; ///< methods 方法信息
@property (nullable, nonatomic, strong, readonly) NSDictionary<NSString *, YYClassPropertyInfo *> *propertyInfos; ///< properties 属性信息

/**
 If the class is changed (for example: you add a method to this class with
 'class_addMethod()'), you should call this method to refresh the class info cache.
 
 After called this method, `needUpdate` will returns `YES`, and you should call 
 'classInfoWithClass' or 'classInfoWithClassName' to get the updated class info.
 */
- (void)setNeedUpdate;

/**
 If this method returns `YES`, you should stop using this instance and call
 `classInfoWithClass` or `classInfoWithClassName` to get the updated class info.
 
 @return Whether this class info need update.
 */
- (BOOL)needUpdate;

/**
 Get the class info of a specified Class.
 
 @discussion This method will cache the class info and super-class info
 at the first access to the Class. This method is thread-safe.
 
 @param cls A class.
 @return A class info, or nil if an error occurs.
 */
+ (nullable instancetype)classInfoWithClass:(Class)cls;

/**
 Get the class info of a specified Class.
 
 @discussion This method will cache the class info and super-class info
 at the first access to the Class. This method is thread-safe.
 
 @param className A class name.
 @return A class info, or nil if an error occurs.
 */
+ (nullable instancetype)classInfoWithClassName:(NSString *)className;

@end

NS_ASSUME_NONNULL_END
