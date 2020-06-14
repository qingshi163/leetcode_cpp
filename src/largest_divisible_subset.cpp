#include "../catch.hpp"
#include "../inc.hpp"

class LC_LargestDivisibleSubset {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        if (nums.empty()) return {};
        sort(nums.begin(), nums.end());
        vector<vector<int>> dp(nums.size());
        return helper(nums, 0, {}, dp);
        // for (int i = 0; i < nums.size(); i++) {
        //     vector<int> v = {nums[i]};
        //     for (int j = 0; j < nums.size(); j++) {
        //         if (j == i) continue;
        //         if (nums[i] % nums[j] == 0 || nums[j] % nums[i] == 0) {
        //             v.push_back(nums[j]);
        //         }
        //     }
        // }
    }
    vector<int> helper(const vector<int>& nums, int i, vector<int> v, vector<vector<int>>& dp) {
        if (i == nums.size()) return v;
        if (!dp[i].empty()) return dp[i];
        vector<int> result2, result;
        if (v.empty() || nums[i] % v.back() == 0) {
            vector<int> v2 = v;
            v2.push_back(nums[i]);
            result2 = helper(nums, i + 1, std::move(v2), dp);
        }
        result = helper(nums, i + 1, std::move(v), dp);
        dp[i] = result2.size() >= result.size() ? result2 : result;
        // return  result2.size() >= result.size() ? result2 : result;
        return dp[i];
    }
};

TEST_CASE("LC: Largest Divisible Subset") {
    auto s = make_shared<LC_LargestDivisibleSubset>();
    vector<int> nums;
    CHECK_THAT(s->largestDivisibleSubset(nums={1,2,3}),
        Catch::UnorderedEquals(vector<int>{1,2}) ||
        Catch::UnorderedEquals(vector<int>{1,3}));
    CHECK_THAT(s->largestDivisibleSubset(nums={1,2,4,8}),
        Catch::UnorderedEquals(vector<int>{1,2,4,8}));
    CHECK_THAT(s->largestDivisibleSubset(nums={1,2,4,8,5,10}),
        Catch::UnorderedEquals(vector<int>{1,2,4,8}));
    CHECK_THAT(s->largestDivisibleSubset(nums={4,8,10,240}),
        Catch::UnorderedEquals(vector<int>{4,8,240}));
    // cout << s->largestDivisibleSubset(nums={1,2,3,4,5,6,7,8,9,10,11,12,13});
    // cout << endl;
    // cout << s->largestDivisibleSubset(nums={472,105,328,922,963,625,827,232,913,832,730,152,697,614,570,639,459,895,70,488,239,596,930,402,904,197,911,126,876,535,597,332,863,870,646,839,878,751,528,959,929,679,7,543,248,353,494,67,841,732,662,122,485,565,318,747,42,545,282,638,228,496,860,874,334,556,103,437,83,61,365,761,259,361,64,612,206,131,452,938,144,573,774,243,521,102,787,154,92,15,649,951,240,506,342,770,940,135,700,820,393,412,884,356,618,366,807,907,861,380,32,921,622,23,760,57,466,416,391,273,706,512,212,998,263,279,743,27,514,98,996,231,905,902,91,636,285,364,609,189,738,368,203,846,6,970,210,748,594,268,157,726,257,419,999,797,869,96,792,451,352,693,894,987,978,595,518,346,315,114,900,160,119,721,218,814,988,477,66,733,740,421,537,642,178,882,21,337,868,350,945,815,219,290,129,684,640,155,409,712,372,222,848,765,932,283,14,819,544,146,425,958,644,903,458,473,85,627,845,641,340,198,961,456,992,495,413,170,390,559,143,166,428,100,809,647,354,619,435,250,837,533,530,883,948,816,432,261,623,560,503,406,916,147,826,277,312,253,729,251,434,443,686,683,944,186,829,898,63,457,405,417,811,579,957,404,532,621,8,260,445,45,887,296,728,236,591,447,422,696,481,893,264,974,701,714,379,12,482,541,942,385,849,345,469,705,527,571,799,962,650,387,552,97,808,971,242,803,36,505,777,89,507,52,47,436,703,716,794,229,628,108,800,779,69,449,165,973,897,324,943,689,917,745,76,873,164,616,9,24,237,739,892,818,718,351,617,420,744,314,687,956,782,781,297,424,737,912,522,272,408,369,645,275,611,840,382,125,890,162,568,295,349,301,997,38,908,179,333,439,899,329,65,159,142,121,923,247,854,802,330,335,43,843,254,137,954,515,790,950,566,857,490,822,519,286,150,583,796,291,941,37,742,723,784,976,374,780,888,569,879,805,88,468,463,969,258,877,176,564,654,798,789,793,401,493,557,592,202,418,115,852,462,953,717,338,480,981,396,634,836,681,629,935,553,540,397,665,758,817,224,821,158,968,323,17,3,776,177,81,906,749,344,169,140,926,118,501,927,504,598,875,34,643,548,813,470,508,736,602,378,59,652,994,915,249,213,661,450,39,267,586,55,727,25,113,141,734,972,872,300,516,526,270,112,555,171,766,256,127,10,316,554,194,448,657,847,174,241,620,68,562,426,133,265,491,909,989,168,173,167,928,41,567,986,724,658,208,699,709,306,933,2,653,881,298,750,577,702,319,694,394,601,651,309,16,310,668,486,192,136,33,856,134,563,370,358,498,593,230,484,308,851,235,51,551,536,980,415,810,246,307,79,221,580,576,101,438,791,455,673,75,610,376,44,624,399,294,271,195,725,637,78,773,806,967,163,871,389,453,558,925,193,467,274,371,788,599});
    // cout << endl;
    // cout << s->largestDivisibleSubset(nums={832,33,531,416,335,298,365,352,582,936,366,305,930,530,97,349,71,295,840,108,299,804,925,627,953,571,658,732,429,136,563,462,666,330,796,315,695,500,896,982,217,200,912,98,297,612,169,943,628,593,959,904,219,240,857,789,897,940,569,384,502,382,401,184,716,230,29,963,211,597,515,122,163,86,215,105,889,842,49,847,267,87,954,407,245,975,719,746,709,471,281,238,186,510,618,149,73,214,663,194,260,825,631,474,519,668,329,718,765,947,156,353,490,962,679,560,59,387,31,692,976,568,201,273,159,730,819,418,906,801,892,672,559,866,389,675,812,744,164,737,57,195,115,933,158,909,598,359,853,314,983,11,395,153,781,301,838,625,704,256,351,996,225,644,521,509,674,417,272,622,937,723,632,331,228,412,181,435,469,157,368,524,38,132,325,420,127,731,771,604,505,634,67,374,894,3,448,878,686,641,316,207,76,363,795,235,770,446,820,493,177,816,615,410,117,944,829,190,831,289,516,964,170,134,671,885,682,119,402,82,485,901,375,68,858,739,56,974,683,884,815,872,715,104,290,348,588,834,788,472,466,867,550,779,65,802,459,440,870,753,608,808,623,642,44,437,865,758,540,506,691,958,854,546,39,595,369,504,63,311,722,441,786,899,338,651,874,946,811,848,939,284,824,309,653,133,514,460,678,54,399,759,468,61,480,783,266,900,400,237,403,534,213,914,473,198,380,373,288,154,844,535,409,249,285,168,69,345,647,851,846,264,102,246,106,648,576,212,438,981,987,379,360,667,95,172,101,580,891,385,747,161,927,361,818,657,171,342,232,734,714,362,425,475,28,41,551,142,131,51,229,9,607,326,522,687,792,845,665,358,91,720,155,565,99,26,650,539,780,589,950,935,372,227,424,750,833,554,841,552,60,757,430,916,140,790,426,776,96,199,923,806,949,755,711,659,911,611,310,774,265,880,690,706,761,286,255,756,204,444,478,601,529,669,241,784,566,528,208,270,511,236,271,378,58,453,467,233,250,567,296,932,989,367,626,35,162,887,572,603,564,797,280,406,970,689,408,431,638,489,85,50,357,803,47,555,793,422,763,110,869,861,253,320,538,347,405,769,64,875,630,537,328,553,166,948,303,160,800,507,920,922,90,693,636,17,455,183,210,856,762,656,174,873,579,176,688,640,1,938,902,341,740,581,427,111,972,443,22,791,304,574,575,725,477,700,817,381,479,248,121,411,547,182,871,599,203,13,224,541,724,178,775,388,4,251,321,52,88,100,279,614,839,84,151,735,40,752,773,376,77,476,708,396,988,961,24,231,445,609,952,965,986,414,451,881,42,257,32,334,130,596,527,94,333,317,244,960,710,852,862,421,81,37,452,274,187,268,520,491,778,18,743,620,145,72,370,118,748,633,997,436,143,573,495,180,34});
    // cout << endl;
    // cout << s->largestDivisibleSubset(nums={3,4,16,8}) << endl;
    // cout << s->largestDivisibleSubset(nums={633,606,592,684,54,149,608,300,135,152,667,953,750,70,578,121,906,656,908,379,254,345,189,642,748,585,192,811,851,483,949,89,540,166,494,40,125,794,526,276,812,830,26,233,407,498,139,62,757,869,101,57,308,200,993,852,362,844,334,311,326,774,850,492,620,890,968,765,767,244,576,597,621,809,3,118,299,417,874,519,83,327,391,878,568,594,240,763,927,902,53,751,932,672,992,899,436,111,363,707,114,523,709,583,173,692,560,487,619,950,716,538,895,307,301,208,741,225,959,248,302,922,35,412,768,272,179,168,797,655,976,840,214,814,458,515,529,347,409,836,647,582,43,387,158,353,410,406,440,418,803,888,813,66,202,609,72,448,286,342,257,871,603,561,58,602,100,340,651,453,102,56,459,785,848,876,939,388,115,973,552,532,527,160,604,55,241,397,567,392,170,952,676,123,445,127,462,579,563,503,389,702,617,285,442,731,610,263,136,505,866,542,815,106,290,382,497,903,801,935,25,486,44,49,381,747,600,997,384,41,727,34,989,832,206,373,352,663,85,987,960,857,556,918,849,261,249,641,995,449,637,730,842,364,74,875,704,905,764,910,630,467,572,292,565,42,421,253,690,901,951,701,591,47,198,580,777,39,295,265,998,380,259,88,847,183,913,639,68,891,256,343,156,59,2,90,454,581,218,493,227,419,109,229,489,835,316,335,369,46,693,760,317,546,868,11,957,280,860,64,607,438,834,715,13,63,203,199,889,128,820,490,36,798,428,724,185,31,159,446,831,16,694,386,775,626,133,332,721,403,172,599,648,524,879,554,92,612,670,95,243,500,110,288,885,675,863,807,964,164,687,222,174,264,817,303,778,545,338,239,574,893,282,956,120,481,859,404,161,287,533,624,771,197,485,723,451,649,758,752,518,520,502,130,643,236,699,211,408,423,466,215,753,886,934,734,525,94,736,623,749,786,833,76,783,275,668,661,841,420,788,443,14,355,625,314,826,184,805,284,943,32,18,224,220,559,441,887,571,658,358,689,383,163,394,60,933,892,262,140,50,165,719,376,330,838,827,1000,588,679,182,629,872,970,351,45,965,372,547,589,116,898,278,117,251,190,194,6,511,104,530,861,846,61,881,739,230,854,683,555,646,678,97,839,12,954,937,558,15,354,740,93,238,298,781,657,426,544,616,368,979,669,738,78,601,268,823,696,65,67,495,787,217,488,38,33,980,252,144,562,339,522,425,281,472,710,982,470,103,907,19,312,825,304,87,424,10,945,210,553,681,390,759,52,569,977,936,640,296,870,305,422,743,195,660,955,204,961,71,69,575,590,659,232,853,754,7,766,962,507,517,940,802,153,631,877,336,944,346,337,433,941,539,947,796,260,270,150,27,474,325,810,399,175,584,416,598,653,465,677,377,427});
    // cout << endl;
}