//
//  MochaRuntime.h
//  Mocha
//
//  Created by Logan Collins on 5/10/12.
//  Copyright (c) 2012 Sunflower Softworks. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JavaScriptCore/JavaScriptCore.h>


@class MOException;
@protocol MochaDelegate;


@interface Mocha : NSObject

+ (Mocha *)sharedRuntime;

- (id)initWithGlobalContext:(JSGlobalContextRef)ctx;

@property (readonly) JSGlobalContextRef context;
@property (assign) id <MochaDelegate> delegate;

// Evaluation
- (id)evalString:(NSString *)string;

// Frameworks
- (id)callFunctionWithName:(NSString *)functionName;
- (id)callFunctionWithName:(NSString *)functionName withArguments:(id)firstArg, ... NS_REQUIRES_NIL_TERMINATION;
- (id)callFunctionWithName:(NSString *)functionName withArgumentsInArray:(NSArray *)arguments;

// Syntax Validation
- (BOOL)isSyntaxValidForString:(NSString *)string;

// Frameworks
- (BOOL)loadFrameworkWithName:(NSString *)frameworkName;
- (BOOL)loadFrameworkWithName:(NSString *)frameworkName inDirectory:(NSString *)directory;

// Garbage Collector
- (void)garbageCollect;

@end


@protocol MochaDelegate <NSObject>

@optional

- (void)mochaRuntime:(Mocha *)aRuntime didEncounterUncaughtException:(MOException *)exception;

@end


@interface NSObject (MochaScripting)

+ (BOOL)isSelectorExcludedFromMochaScript:(SEL)aSelector;

- (void)finalizeForMochaScript;

@end


@interface NSObject (MochaObjectSubscripting)

// Indexed subscripts
- (id)objectForIndexedSubscript:(NSUInteger)index;
- (void)setObject:(id)object forIndexedSubscript:(NSUInteger)index;

// Keyed subscripts
- (id)objectForKeyedSubscript:(NSString *)key;
- (void)setObject:(id)object forKeyedSubscript:(NSString *)key;

@end