//
// Copyright 2016 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#import "Delegate/GREYSurrogateDelegate.h"

#import "Common/GREYDefines.h"


@interface GREYSurrogateDelegate()
/**
 *  Original delegate being proxied.
 */
@property(weak, nonatomic, readwrite) id weakOriginalDelegate;
/**
 *  Strong Original delegate being proxied.
 */
@property(nonatomic, readwrite) id strongOriginalDelegate;
@end


@implementation GREYSurrogateDelegate {
  /**
   *  Indicates whether the original delegate is held weakly or strongly.
   */
  BOOL _isWeak;
}

- (instancetype)initWithOriginalDelegate:(id)originalDelegate
                            isWeak:(BOOL)shouldBeWeak {
  self = [super init];
  if (self) {
    if (shouldBeWeak) {
      self.weakOriginalDelegate = originalDelegate;
    } else {
      self.strongOriginalDelegate = originalDelegate;
    }
    _isWeak = shouldBeWeak;
  }
  return self;
}

#pragma mark - Message forwarding

- (BOOL)respondsToSelector:(SEL)aSelector {
  return [super respondsToSelector:aSelector]
      || [self.originalDelegate respondsToSelector:aSelector];
}
- (BOOL)isKindOfClass:(Class)aClass {
  return [super isKindOfClass:aClass]
      || [self.originalDelegate isKindOfClass:aClass];
}
- (BOOL)conformsToProtocol:(Protocol *)aProtocol {
  return [super conformsToProtocol:aProtocol]
      || [self.originalDelegate conformsToProtocol:aProtocol];
}
- (id)originalDelegate {
  return _isWeak ? self.weakOriginalDelegate : self.strongOriginalDelegate;
}

////+ (BOOL)resolveClassMethod:(SEL)sel{  //指定是否动态添加方法。
////    return true;
////}
+ (BOOL)resolveInstanceMethod:(SEL)sel{ //you can add some method here
    return NO;
}
- (id)forwardingTargetForSelector:(SEL)aSelector {
    return self.originalDelegate;
}
- (NSMethodSignature *)methodSignatureForSelector:(SEL)aSelector {
    NSMethodSignature *proxyMethodSignatureForSelector =
    [[self originalDelegate] methodSignatureForSelector:aSelector];
    if (proxyMethodSignatureForSelector) {
        return proxyMethodSignatureForSelector;
    }
    NSMethodSignature *superMethodSignatureForSelector = [super methodSignatureForSelector:aSelector];
    if (superMethodSignatureForSelector) {
        return superMethodSignatureForSelector;
    }
    return nil;//not process and not crash
}
//-(void) forwardInvocation:(NSInvocation *)anInvocation{
////    可以通过anInvocation对象做很多处理，比如修改实现方法，修改响应对象等
//}  //or
//-(void)doesNotRecognizeSelector:(SEL)aSelector{
//}
////    crash if not impl both of them

//第一步：+ (BOOL)resolveInstanceMethod:(SEL)sel实现方法，指定是否动态添加方法。
//若返回NO，则进入下一步，若返回YES，则通过class_addMethod函数动态地添加方法，消息得到处理，此流程完毕。
//
//第二步：在第一步返回的是NO时，就会进入- (id)forwardingTargetForSelector:(SEL)aSelector方法，
//这是运行时给我们的第二次机会，用于指定哪个对象响应这个selector。
//不能指定为self。
//若返回nil，表示没有响应者，则会进入第三步。
//若返回某个对象，则会调用该对象的方法。
//

//第三步：若第二步返回的是nil，则我们首先要通过- (NSMethodSignature *)methodSignatureForSelector:(SEL)aSelector指定方法签名，
//若返回nil，则表示不处理。
//若返回方法签名，则会进入下一步。
//
//第四步：当第三步返回方法方法签名后，就会调用- (void)forwardInvocation:(NSInvocation *)anInvocation方法，
//我们可以通过anInvocation对象做很多处理，比如修改实现方法，修改响应对象等
//
//第五步：若没有实现- (void)forwardInvocation:(NSInvocation *)anInvocation方法，那么会进入
//- (void)doesNotRecognizeSelector:(SEL)aSelector方法。若我们没有实现这个方法，
//那么就会crash，然后提示打不到响应的方法。到此，动态解析的流程就结束了。

@end

