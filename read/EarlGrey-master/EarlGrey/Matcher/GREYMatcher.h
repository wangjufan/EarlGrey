//
#import <Foundation/Foundation.h>
#import <EarlGrey/GREYDescription.h>
NS_ASSUME_NONNULL_BEGIN
/**
 *  Matchers are another way of expressing simple or complex logical expressions. This protocol
 *  defines a set of methods that must be implemented by every matcher object.
 */
@protocol GREYMatcher<NSObject>
/**
 *  A method to evaluate the matcher for the provided @c item.
 *  @param item The object which is to be evaluated against the matcher.
 *  @return @c YES if the object matched the matcher, @c NO otherwise.
 */
- (BOOL)matches:(_Nullable id)item;
/**
 *  A method to generate a description of an object.
 *  @param description The description that is built or appended.
 */
- (void)describeTo:(id<GREYDescription>)description;

/**
 *  A method to evaluate the matcher for the provided @c item with a description for the issue
 *  in case of a mismatch.
 *
 *  @param item                The object which is to be evaluated against the matcher.
 *
 *  @param mismatchDescription The description that is built or appended if the provided @c item
 *                             does not match the matcher.
 *
 *  @return @c YES if the object matched the matcher, @c NO otherwise. In case of a mismatch, the
 *             reason for mismatch is added to @c mismatchDescription.
 */
- (BOOL)matches:(_Nullable id)item
describingMismatchTo:(id<GREYDescription>)mismatchDescription;
/**
 *  A method to generate the description containing the reason for why a matcher did not match an
 *  item.
 *  @param item                The object which is to be evaluated against the matcher.
 *  @param mismatchDescription The description that is built or appended if the provided @c item
 *                             does not match the matcher.
 *  @remark This method assumes that GREYMatcher::matches: is false, but will not check this.
 */
- (void)describeMismatchOf:(_Nullable id)item to:(id<GREYDescription>)mismatchDescription;
@end
NS_ASSUME_NONNULL_END

