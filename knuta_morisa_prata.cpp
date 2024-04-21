#include <vector>
#include <chrono>
#include "SubstringSearcher.hpp"

void substring_searcher_app(std::vector<std::chrono::duration<double>>& all_results, bool isPrint);

void calculate_prefix_function(const std::string& sub_str,
                               std::vector<size_t>& pi_func,
                               int count_of_opers)
{
    // Первый элемент префиксной функции
    pi_func[0] = 0;

    size_t temp = 0;
    for (size_t pos = 1; pos < sub_str.length() ; ++pos) {
        // Пока текущий символ не совпадает с предыдущим, сдвигаемся назад
        while (temp > 0 && sub_str[pos] != sub_str[temp]) {
            temp = pi_func[temp - 1];

            ++count_of_opers; // + кол-во опер. сравнения
        }
        ++count_of_opers; // + кол-во опер. сравнения


        // Если символы совпадают, увеличиваем счетчик
        if (sub_str[pos] == sub_str[temp]) {
            ++temp;

            ++count_of_opers; // + кол-во опер. сравнения
        } else {
            ++count_of_opers; // + кол-во опер. сравнения
        }

        // Сохраняем значение префиксной функции для текущего символа
        pi_func[pos] = temp;

        ++count_of_opers; // + кол-во опер. сравнения
    }
    ++count_of_opers; // + кол-во опер. сравнения
 }

 int64_t SubstringSearcher::algorithm() {
    // Префиксная функция
    std::vector<size_t> pi_func(m_sub_str.length(), 0);
    calculate_prefix_function(m_sub_str, pi_func, m_count_of_opers);

    size_t temp = 0;

    for (size_t pos = 0; pos < m_full_str.length(); ++pos) {
        // Пока текущий символ не совпадает с предыдущим, сдвигаемся назад
        while (temp > 0 && m_full_str[pos] != m_sub_str[temp]) {
            temp = pi_func[temp - 1];

            ++m_count_of_opers; // + кол-во опер. сравнения
        }
        ++m_count_of_opers; // + кол-во опер. сравнения


        // Если символы совпадают, увеличиваем счетчик
        if (m_full_str[pos] == m_sub_str[temp]) {
            ++temp;

            ++m_count_of_opers; // + кол-во опер. сравнения
        } else {
            ++m_count_of_opers; // + кол-во опер. сравнения
        }

        // Если достигнут конец подстроки, возвращаем позицию начала подстроки в тексте
        if (temp == m_sub_str.length()) {
            ++m_count_of_opers; // + кол-во опер. сравнения
            
            return static_cast<int64_t>(pos - (m_sub_str.length() - 1));
        } else {
            ++m_count_of_opers; // + кол-во опер. сравнения
        }

        ++m_count_of_opers; // + кол-во опер. сравнения
    }
    ++m_count_of_opers; // + кол-во опер. сравнения


    // Возвращаем -1, если подстрока не найдена
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
