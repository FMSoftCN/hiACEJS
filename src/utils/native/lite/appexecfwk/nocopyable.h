/*
 * Copyright (c) 2020 FMSoft.
 */

#ifndef OHOS_NOCOPYABLE_H
#define OHOS_NOCOPYABLE_H

namespace OHOS {
#define DISALLOW_COPY_AND_MOVE(className)               \
    DISALLOW_COPY(className);                           \
    DISALLOW_MOVE(className)

#define DISALLOW_COPY(className)                        \
    className(const className&) = delete;               \
    className& operator= (const className&) = delete

#define DISALLOW_MOVE(className)                        \
    className(className&&) = delete;                    \
    className& operator= (className&&) = delete


class NoCopyable {
protected:
    NoCopyable() {};
    virtual ~NoCopyable() {};

private:
    DISALLOW_COPY_AND_MOVE(NoCopyable);
};
}  // namespace OHOS
#endif  // OHOS_NOCOPYABLE_H
