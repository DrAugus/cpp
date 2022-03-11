//
// daily.cpp
// Created by AUGUS on 2022/3/11.
//

#include <augus/augus.h>

enum class DailyType {
  Document,
  PreStudy,
  CodeTest,
  Meeting,
  BugFix,
  Support,
  Other,
};

static std::map<DailyType, std::string> MapDailyType = {
    {DailyType::Document, "文档"},
    {DailyType::PreStudy, "预研"},
    {DailyType::CodeTest, "开发/测试"},
    {DailyType::Meeting, "会议"},
    {DailyType::BugFix, "bug修复"},
    {DailyType::Support, "支持"},
    {DailyType::Other, "其他"},
};

enum class DailyKind {
  D, W
};

struct DailyDefine {
  DailyType daily_type_;
  DailyKind daily_kind_;
  std::string msg_;
};

bool Contain(const std::string &str_find, const std::string &str) {
  std::string::size_type index = str.find(str_find);
  return index != std::string::npos;
}

void WriteDaily(const DailyDefine &daily_define) {
  auto str_daily_type = MapDailyType[daily_define.daily_type_];

  std::ifstream in_file;
  in_file.open("../../../src/auto/daily.txt", std::ios::binary);
  std::string line;
  while (std::getline(in_file, line)) {
    if (Contain(line, str_daily_type)) {
      std::ofstream out_file;
      out_file.open("../../../src/auto/daily.txt", std::ios::app);
      out_file << " > " << daily_define.msg_ << std::endl;
      out_file.close();
    } else {
      std::ofstream out_file;
      out_file.open("../../../src/auto/daily.txt", std::ios::app);
      out_file << MapDailyType[daily_define.daily_type_] << ": " << std::endl;
      out_file << " > " << daily_define.msg_ << std::endl;
      out_file.close();
    }
  }

  in_file.close();

}

void SetDaily() {
  for (auto i = 0; static_cast<DailyType>(i) <= DailyType::Other; ++i) {
    std::cout << i << std::endl;
    DailyDefine daily_define{};
    daily_define.daily_type_ = (DailyType) i;
    daily_define.daily_kind_ = DailyKind::D;
    daily_define.msg_ = "uuu";
    WriteDaily(daily_define);
  }

}

int main() {
  SetDaily();
  return 0;
}