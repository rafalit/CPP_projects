#include <array>
#include <memory>
#include <numeric> // std::iota()
#include <benchmark/benchmark.h>
#include "../containerWrapper.h"

/// Pierwszy raz cos napisalem w bibliotece gbenchmark - prosze sie na tym nie wzorowac!

namespace
{
    constexpr size_t N = 100'000;

    using value_type = IContainerWrapper::value_type;

    static auto prepareSourceContainer()
    {
        std::array<value_type, N> sourceElements;

        std::iota(sourceElements.begin(), sourceElements.end(), 0);
        return sourceElements;
    }
} // namespace


static void BM_constructionLotsOfElementsWithDefaultConstructor(benchmark::State& state)
{
    for (auto _ : state)
    {
        std::unique_ptr<ContainerWrapper[]> wrappers(new ContainerWrapper[N]);
        static_cast<void>(wrappers); // to disable warning
    }
}
BENCHMARK(BM_constructionLotsOfElementsWithDefaultConstructor);


static void BM_constructionFromArray(benchmark::State& state)
{
    const auto sourceElements = prepareSourceContainer();

    for (auto _ : state)
    {
        ContainerWrapper wrapper(sourceElements.data(), sourceElements.size());
        static_cast<void>(wrapper); // to disable warning
    }
}
BENCHMARK(BM_constructionFromArray);


static void BM_pushBackManyElements(benchmark::State& state)
{
    const auto sourceElements = prepareSourceContainer();

    for (auto _ : state)
    {
        ContainerWrapper wrapper;
        for (const auto& element : sourceElements)
        {
            wrapper.push_back(element);
        }
    }
}
BENCHMARK(BM_pushBackManyElements);


static void BM_pushFrontManyElements(benchmark::State& state)
{
    const auto sourceElements = prepareSourceContainer();

    for (auto _ : state)
    {
        ContainerWrapper wrapper;
        for (const auto& element : sourceElements)
        {
            wrapper.push_front(element);
        }
    }
}
BENCHMARK(BM_pushFrontManyElements);


static void BM_insertingInRandomPositionManyElements(benchmark::State& state)
{
    const auto sourceElements = prepareSourceContainer();

    for (auto _ : state)
    {
        ContainerWrapper wrapper;
        for (const auto& element : sourceElements)
        {
            const size_t position = wrapper.size() > 0 ? rand() % wrapper.size() : 0;
            wrapper.insert(element, position);
        }
    }
}
BENCHMARK(BM_insertingInRandomPositionManyElements);


static void BM_randomAccess(benchmark::State& state)
{
    const auto sourceElements = prepareSourceContainer();

    ContainerWrapper wrapper(sourceElements.data(), sourceElements.size());

    for (auto _ : state)
    {
        const size_t position = rand() % wrapper.size();
        wrapper.at(position);
    }
}
BENCHMARK(BM_randomAccess);


static void BM_sorting(benchmark::State& state)
{
    auto sourceElements = prepareSourceContainer();
    decltype(sourceElements) reversedElements;
    std::reverse_copy(begin(sourceElements), end(sourceElements), begin(reversedElements));

    for (auto _ : state)
    {
        ContainerWrapper wrapper(reversedElements.data(), sourceElements.size());
        wrapper.sort();
    }
}
BENCHMARK(BM_sorting);


static void BM_randomErase(benchmark::State& state)
{
    const auto sourceElements = prepareSourceContainer();

    for (auto _ : state)
    {
        ContainerWrapper wrapper(sourceElements.data(), sourceElements.size());

        for (size_t i=1; i < N; ++i)
        {
            const size_t erasePosition = wrapper.size() > 0 ? rand() % wrapper.size() : 0;
            wrapper.erase(erasePosition);
        }
    }
}
BENCHMARK(BM_randomErase);


static void BM_count_expectedAllElementsCounted(benchmark::State& state)
{
    const auto sourceElements = prepareSourceContainer();

    const ContainerWrapper wrapper(sourceElements.data(), sourceElements.size());

    for (auto _ : state)
    {
        wrapper.count();
    }
}
BENCHMARK(BM_count_expectedAllElementsCounted);


static void BM_findElement(benchmark::State& state)
{
    const auto sourceElements = prepareSourceContainer();

    const ContainerWrapper wrapper(sourceElements.data(), sourceElements.size());

    for (auto _ : state)
    {
        for (size_t i=0; i < N / 10; ++i)
        {
            const size_t expectedPosition = rand() % sourceElements.size();
            const auto element2Find = sourceElements[expectedPosition];
            wrapper.find(element2Find);
        }
    }
}
BENCHMARK(BM_findElement);


static void BM_popBack(benchmark::State& state)
{
    const auto sourceElements = prepareSourceContainer();

    for (auto _ : state)
    {
        ContainerWrapper wrapper(sourceElements.data(), sourceElements.size());
        for (size_t i=0; i < N; ++i)
        {
            wrapper.pop_back();
        }
    }
}
BENCHMARK(BM_popBack);


static void BM_popFront(benchmark::State& state)
{
    const auto sourceElements = prepareSourceContainer();

    for (auto _ : state)
    {
        ContainerWrapper wrapper(sourceElements.data(), sourceElements.size());
        for (size_t i=0; i < N; ++i)
        {
            wrapper.pop_front();
        }
    }
}
BENCHMARK(BM_popFront);
