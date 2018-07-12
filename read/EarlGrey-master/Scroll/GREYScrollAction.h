#import <EarlGrey/GREYBaseAction.h>
#import <EarlGrey/GREYConstants.h>
NS_ASSUME_NONNULL_BEGIN
/**
 *  A GREYAction that implements the scroll action.
 */
@interface GREYScrollAction : GREYBaseAction
/**
 *  @remark init is not an available initializer. Use the other initializers.
 */
- (instancetype)init NS_UNAVAILABLE;
/**
 *  @remark initWithName::constraints: is overridden from its superclass.
 */
- (instancetype)initWithName:(NSString *)name
                 constraints:(id<GREYMatcher>)constraints NS_UNAVAILABLE;
/**
 *  Creates a scroll action that scrolls the contents in the given @c direction for the
 *  given @c amount.
 *  @param direction The direction of the scroll.
 *  @param amount    The amount specified in points. The units here are the same as the units
 *                   of the coordinate system of the element matched.
 *  @return An instance of GREYScrollAction, initialized with the provided
 *          direction and scroll amount.
 */
- (instancetype)initWithDirection:(GREYDirection)direction amount:(CGFloat)amount;
/**
 *  Creates a scroll action that scrolls the contents in the given @c direction for the
 *  given @c amount with the start point specified by @c startPointPercents.
 *  @param direction          The direction of the scroll.
 *  @param amount             The amount specified in points. The units here are the same as the
 *                            units of the coordinate system of the element matched.
 *  @param startPointPercents The start point of the scroll specified as percents (0, 1) exclusive,
 *                            in the visible area of the scroll view or as @c NAN to pick a point
 *                            that provides maximum scroll length.
 *  @return An instance of GREYScrollAction, initialized with the provided
 *          direction, scroll amount and start point.
 */
- (instancetype)initWithDirection:(GREYDirection)direction
                        amount:(CGFloat)amount
               startPointPercents:(CGPoint)startPointPercents NS_DESIGNATED_INITIALIZER;
@end
NS_ASSUME_NONNULL_END

