#include <memory>
#include <iostream>
#include <utility>

/**
 * Имеет смысл использовать паттерн Строитель только тогда, когда ваши продукты
 * достаточно сложны и требуют обширной конфигурации.
 *
 * В отличие от других порождающих паттернов, различные конкретные строители
 * могут производить несвязанные продукты. Другими словами, результаты различных
 * строителей могут не всегда следовать одному и тому же интерфейсу.
 */

enum HouseType {
    WOODEN = 1,
    STEEL = 2
};

struct House {
    bool hasWindows_ = false;
    bool hasDoors_ = false;
    bool hasWalls_ = false;
    HouseType type_;
};

std::ostream& operator<<(std::ostream& os, const House& house) {
    os << std::boolalpha << "House type - "  << house.type_       << '\n'
                         << "Has windows - " << house.hasWindows_ << '\n'
                         << "Has doors - "   << house.hasDoors_   << '\n'
                         << "Has walls - "   << house.hasWalls_   << '\n';
    return os;
}

class HouseBuilder {
public:
    virtual void produceWindows() const = 0;
    virtual void produceDoors() const = 0;
    virtual void produceWalls() const = 0;
    virtual ~HouseBuilder() {}
};

using HousePtr = std::unique_ptr<House>;
using HouseBuilderPtr = std::unique_ptr<HouseBuilder>;
using HouseBuilderSPtr = std::shared_ptr<HouseBuilder>;

class WoodenHouseBuilder : public HouseBuilder {
public:
    WoodenHouseBuilder() {
        reset();
    }
    ~WoodenHouseBuilder() {};

    HousePtr getHouse() {
        auto result = std::move(house_);
        reset();
        return result;
    }

    void produceWindows() const override {
        house_->hasWindows_ = true;
        house_->type_ = HouseType::WOODEN;
    }
    void produceDoors() const override {
        house_->hasDoors_ = true;
        house_->type_ = HouseType::WOODEN;
    }
    void produceWalls() const override {
        house_->hasWalls_ = true;
        house_->type_ = HouseType::WOODEN;
    };

private:
    void reset() {
        house_ = std::make_unique<House>();
    }

    HousePtr house_;
};

class SteelHouseBuilder : public HouseBuilder {
public:
    SteelHouseBuilder() {
        reset();
    }
    ~SteelHouseBuilder() {};

    HousePtr getHouse() {
        auto result = std::move(house_);
        reset();
        return result;
    }

    void produceWindows() const override {
        house_->hasWindows_ = true;
        house_->type_ = HouseType::STEEL;
    }
    void produceDoors() const override {
        house_->hasDoors_ = true;
        house_->type_ = HouseType::STEEL;
    }
    void produceWalls() const override {
        house_->hasWalls_ = true;
        house_->type_ = HouseType::STEEL;
    };

private:
    void reset() {
        house_ = std::make_unique<House>();
    }

    HousePtr house_;
};

class Director {
public:
    void setBuilder(HouseBuilderSPtr builder) {
        builder_ = std::move(builder);
    }

    void buildMinimumHouse() {
        builder_->produceWalls();
    }

    void buildFullHouse() {
        builder_->produceWalls();
        builder_->produceDoors();
        builder_->produceWindows();
    }
private:
    HouseBuilderSPtr builder_ = nullptr;
};