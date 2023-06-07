#include "matchers/describe-message-matcher.h"

bool compareChannelLists(const ChannelList *a, const ChannelList *b)
{
    EXPECT_EQ(a->getCount(), b->getCount());

    for (int i = 0; i < a->getCount(); i++)
    {
        const UnprovisionedChannel * const *aCh = a->getItem(i);
        const UnprovisionedChannel * const *bCh = b->getItem(i);
        EXPECT_EQ((*aCh)->getId(), (*bCh)->getId()) << "Expected id for channel " << i << " \"" << (*aCh)->getId() << "\" got \"" << (*bCh)->getId() << "\"";
        const char *aName;
        int aLength = 0;
        const char *bName;
        int bLength = 0;
        (*aCh)->getName(&aName, aLength);
        (*bCh)->getName(&bName, bLength);
        EXPECT_STREQ(aName, bName) << "Expected name for channel " << i << " \"" << aName << "\" got \"" << bName << "\"";

        const List<ChannelMode> *aModes = (*aCh)->getSupportedModes();
        const List<ChannelMode> *bModes = (*bCh)->getSupportedModes();

        EXPECT_EQ(aModes->getCount(), bModes->getCount()) << "Expected supported modes for channel " << i << " \"" << aModes->getCount() << "\" got \"" << bModes->getCount() << "\"";
        for (int j = 0; j < aModes->getCount(); j++)
        {
            EXPECT_TRUE(bModes->contains(aModes->getItem(j))) << "Expected mode " << *aModes->getItem(j) << " to be supported for channel " << i;
            EXPECT_TRUE((*bCh)->supportsMode(*aModes->getItem(j))) << "Expected mode " << *aModes->getItem(j) << " to be supported for channel " << i;
        }

        const List<ChannelType> *aTypes = (*aCh)->getSupportedTypes();
        const List<ChannelType> *bTypes = (*bCh)->getSupportedTypes();

        EXPECT_EQ(aTypes->getCount(), bTypes->getCount()) << "Expected supported modes for channel " << i << " \"" << aTypes->getCount() << "\" got \"" << bModes->getCount() << "\"";
        for (int j = 0; j < aTypes->getCount(); j++)
        {
            EXPECT_TRUE(bTypes->contains(aTypes->getItem(j))) << "Expected type " << *aTypes->getItem(j) << " to be supported for channel " << i;
            EXPECT_TRUE((*bCh)->supportsType(*aTypes->getItem(j))) << "Expected type " << *aTypes->getItem(j) << " to be supported for channel " << i;
        }
    }

    return true;
}
