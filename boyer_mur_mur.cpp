#include <unordered_map>
#include <chrono>
#include <vector>
#include "SubstringSearcher.hpp"


void substring_searcher_app(std::vector<std::chrono::duration<double>>& all_results, bool isPrint);


void create_shift_table(const std::string& str,
                        std::unordered_map<char, std::size_t>& shift_table,
                        int count_of_opers)
{
    // Счетчик сдвига
    int shift_number = 1;

    for (auto riter = str.rbegin() + 1; riter != str.rend(); ++riter) {
        // Если символ еще не встречался, добавляем его в таблицу сдвигов
        if (!shift_table.contains(*riter)) {
            (shift_table)[*riter] = shift_number; 
        }
        ++count_of_opers; // + кол-во опер. сравнения 

        ++shift_number;
        
        ++count_of_opers; // + кол-во опер. сравнения
    }
    ++count_of_opers; // + кол-во опер. сравнения

    // Добавляем последний символ в таблицу сдвигов, если он еще не был добавлен
    if (!shift_table.contains(*str.rbegin())) {
        (shift_table)[*str.rbegin()] = shift_number;
        ++count_of_opers; // + кол-во опер. сравнения
    } else {
        ++count_of_opers; // + кол-во опер. сравнения
    }
}

int64_t SubstringSearcher::algorithm() {
    // Таблица сдвигов
    std::unordered_map<char, std::size_t> shift_table;
    create_shift_table(m_sub_str, shift_table, m_count_of_opers);

    size_t sub_lens = m_sub_str.size();
    size_t pos = sub_lens - 1;
    while (pos < m_full_str.size()) {
        // Если текущий символ не совпадает с последним символом подстроки
        if (m_full_str[pos] != m_sub_str[sub_lens - 1]) {
            // Если символ есть в таблице сдвигов, используем его для сдвига
            if (shift_table.contains(m_full_str[pos])) {
                pos += shift_table[m_full_str[pos]];

                ++m_count_of_opers; // + кол-во опер. сравнения
            } else {
                // Иначе сдвигаемся на длину подстроки
                pos += sub_lens;

                ++m_count_of_opers; // + кол-во опер. сравнения
            }

            ++m_count_of_opers; // + кол-во опер. сравнения

        } else {
            // Проверка, совпадает ли подстрока с текущей позицией
            bool match = true;
            size_t r_pos_of_checking_elem = 1;

            while (r_pos_of_checking_elem < sub_lens) {

                if (m_full_str[pos - r_pos_of_checking_elem] !=
                    m_sub_str[sub_lens - 1 - r_pos_of_checking_elem]) {

                        ++m_count_of_opers; // + кол-во опер. сравнения

                        match = false;
                        pos += sub_lens;
                        break;
                } else {
                    ++m_count_of_opers; // + кол-во опер. сравнения
                }

                r_pos_of_checking_elem++;

                ++m_count_of_opers; // + кол-во опер. сравнения

            }
            ++m_count_of_opers; // + кол-во опер. сравнения


            // Если подстрока совпадает, возвращаем позицию
            if (match) {
                ++m_count_of_opers; // + кол-во опер. сравнения

                return static_cast<int64_t>(pos - sub_lens + 1);
            } else {
                ++m_count_of_opers; // + кол-во опер. сравнения
            }

            ++m_count_of_opers; // + кол-во опер. сравнения
        }
        ++m_count_of_opers; // + кол-во опер. сравнения
    }
    ++m_count_of_opers; // + кол-во опер. сравнения

    // Если подстрока не найдена, возвращаем -1
    return -1;
}


 auto main() -> int {
    // ПРОГОН НА 100
    std::vector<std::chrono::duration<double>> all_results(9, static_cast<std::chrono::duration<double>>(0));

    std::vector<std::chrono::duration<double>> one_run(9);

    {
        substring_searcher_app(one_run, true);

        for (int j = 0; j < 9; ++j) {
            all_results[j] += one_run[j];
        }
    }

    for (int i = 1; i < 100; ++i) {
        substring_searcher_app(one_run, false);

        for (int j = 0; j < 9; ++j) {
            all_results[j] += one_run[j];
        }
    }

    for (int i = 0; i < 9; ++i) {
            all_results[i] /= 100;
    }

    std::cout << "AVERAGE RESULT ON 100 RUNNUNGS" << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout << "bad_" << i + 1 << std::endl;
        std::cout << all_results[i].count() << " s" << std::endl; 
    }
    for (int i = 4; i < 8; ++i) {
        std::cout << "good_" << i - 3 << std::endl;
        std::cout << all_results[i].count() << " s" << std::endl;
    }
    std::cout << "average" << std::endl;
    std::cout << all_results[8].count() << " s" << std::endl;

    return 0;
}

void substring_searcher_app(std::vector<std::chrono::duration<double>>& all_results, bool isPrint) {
    std::vector<std::pair<std::string, std::string>> test_files = {
        {"../benchmarks/bad_t_1.txt", "../benchmarks/bad_w_1.txt"},
        {"../benchmarks/bad_t_2.txt", "../benchmarks/bad_w_2.txt"},
        {"../benchmarks/bad_t_3.txt", "../benchmarks/bad_w_3.txt"},
        {"../benchmarks/bad_t_4.txt", "../benchmarks/bad_w_4.txt"},
        {"../benchmarks/good_t_1.txt", "../benchmarks/good_w_1.txt"},
        {"../benchmarks/good_t_2.txt", "../benchmarks/good_w_2.txt"},
        {"../benchmarks/good_t_3.txt", "../benchmarks/good_w_3.txt"},
        {"../benchmarks/good_t_4.txt", "../benchmarks/good_w_4.txt"}
    };

    // ALL TESTS
    std::chrono::duration<double> all_elapsed{};

    int num = 0;
    for (auto test: test_files) {
        if (isPrint) {
            std::cout << "Test on text: " << test.first << std::endl;
        }

        SubstringSearcher substr_searcher(test.first, test.second);

        // ALGHORITM 1 TEST TIME START
        auto start = std::chrono::high_resolution_clock::now();

        auto result = substr_searcher.algorithm();

        auto end = std::chrono::high_resolution_clock::now();

        // ALGHORITM 1 TEST TIME END
        std::chrono::duration<double> elapsed = end - start;

        all_elapsed += elapsed;

        if (isPrint) {
            std::cout << "Result: " << result << std::endl;
            std::cout << "Time: " << elapsed.count() << " s" << std::endl;
            std::cout << "Count of opers: " << substr_searcher.get_count_of_opers() << std::endl;

            std::cout << std::endl;
        }

        all_results[num] = elapsed;

        ++num;
    }

    auto average_time = all_elapsed/(test_files.size());

    if (isPrint) {
        std::cout << "Average time: " << average_time.count() << std::endl;
    }

    all_results[num] = average_time;
}
