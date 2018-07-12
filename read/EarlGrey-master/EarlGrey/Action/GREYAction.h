#import <Foundation/Foundation.h>
NS_ASSUME_NONNULL_BEGIN
/*
 1 坐标转换原则
 2 触摸路径生成原则
 3 路径数据合成事件与注入原则
 4 合成过程
 */
/**
 *  A protocol for actions that are ==== performed on  --- accessibility elements.
 */
@protocol GREYAction<NSObject>
/**
 *  Perform the action specified by the GREYAction object on an @c element
 *  ===  if and only if the @c element matches the constraints of the action.
 *  @param      element    The element the action is to be performed on. This must not be @c nil.
 *  @param[out] errorOrNil Error that will be populated on failure. The implementing class should
 *                         handle the behavior when it is @c nil by, for example, logging the error
 *                         or throwing an exception.
 *  @return @c YES if the action succeeded,
 *          else @c NO. If an action returns @c NO,
 *          it does not mean that the action was not performed at all
 *          but somewhere during the action execution the error occured
 *          and so the UI may be in an unrecoverable state.
 */
- (BOOL)perform:(id)element error:(__strong NSError *_Nullable *)errorOrNil;
/**
 *  A method to get the name of this action.
 *  @return The name of the action.
 *      If the action fails, then the name is printed along with all other relevant information.
 */
- (NSString *)name;
@end
NS_ASSUME_NONNULL_END

