# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -fPIC $(shell pkg-config --cflags Qt6Widgets)
LDFLAGS = $(shell pkg-config --libs Qt6Widgets)

# MOC для Qt
MOC = /usr/lib/qt6/moc

# Файлы проекта
SRC_DIR = .
TARGET = calculator

SOURCES += $(SRC_DIR)/main.cpp
SOURCES += $(SRC_DIR)/MainWindow.cpp
SOURCES += $(SRC_DIR)/Calculator.cpp

HEADERS += $(SRC_DIR)/MainWindow.h
HEADERS += $(SRC_DIR)/Calculator.h

MOC_HEADERS = $(SRC_DIR)/MainWindow.h
MOC_SOURCES = $(MOC_HEADERS:.h=.moc.cpp)

OBJECTS = $(SOURCES:.cpp=.o) $(MOC_SOURCES:.cpp=.o)


# Кросс-компиляция для Windows через MXE
ifeq ($(CROSS),win)
    MXE_PATH = $(HOME)/git/mxe
    MXE_TARGET = x86_64-w64-mingw32.shared
    MXE_GNU= x86_64-pc-linux-gnu
    CXX = $(MXE_PATH)/usr/bin/$(MXE_TARGET)-g++
    MOC = $(MXE_PATH)/usr/$(MXE_GNU)/qt6/libexec/moc
    PKG_CONFIG = $(MXE_PATH)/usr/bin/$(MXE_TARGET)-pkg-config

    CXXFLAGS = -std=c++17 -Wall -I$(SRC_DIR) $(shell $(PKG_CONFIG) --cflags Qt6Widgets)
    LDFLAGS = $(shell $(PKG_CONFIG) --libs Qt6Widgets)
    TARGET = calculator.exe

    # Путь к DLL для копирования
    DLL_PATH = $(MXE_PATH)/usr/$(MXE_TARGET)/bin
    DLL_QT6_PATH = $(MXE_PATH)/usr/$(MXE_TARGET)/qt6/bin

endif

# Основная цель
all: $(TARGET)

# Копируем DLL для Windows сборки
ifeq ($(CROSS),win)
	@echo "Копирование DLL..."
	@mkdir -p release/platforms
	@cp $(DLL_QT6_PATH)/Qt6Core.dll release/ 2>/dev/null || true
	@cp $(DLL_QT6_PATH)/Qt6Gui.dll release/ 2>/dev/null || true
	@cp $(DLL_QT6_PATH)/Qt6Widgets.dll release/ 2>/dev/null || true
	@cp $(DLL_PATH)/libgcc_s_seh-1.dll release/ 2>/dev/null || true
	@cp $(DLL_PATH)/libstdc++-6.dll release/ 2>/dev/null || true
	@cp $(DLL_PATH)/libwinpthread-1.dll release/ 2>/dev/null || true
	@cp $(DLL_PATH)/zlib1.dll release/ 2>/dev/null || true
	@cp $(DLL_PATH)/libfreetype-6.dll release/ 2>/dev/null || true
	@cp $(DLL_PATH)/libharfbuzz-0.dll release/ 2>/dev/null || true
	@cp $(DLL_PATH)/libpng16-16.dll release/ 2>/dev/null || true
	@cp $(DLL_PATH)/libbz2.dll release/ 2>/dev/null || true
	@cp $(DLL_PATH)/libglib-2.0-0.dll release/ 2>/dev/null || true
	@cp $(DLL_PATH)/libpcre2-16-0.dll release/ 2>/dev/null || true
	@cp $(DLL_PATH)/libbrotlidec.dll release/ 2>/dev/null || true
	@cp $(DLL_PATH)/libbrotlicommon.dll release/ 2>/dev/null || true
	@cp $(DLL_PATH)/libintl-8.dll release/ 2>/dev/null || true
	@cp $(DLL_PATH)/libiconv-2.dll release/ 2>/dev/null || true
	@cp $(DLL_PATH)/libgraphite2.dll release/ 2>/dev/null || true
	@cp $(MXE_PATH)/usr/$(MXE_TARGET)/qt6/plugins/platforms/qwindows.dll release/platforms/
	@cp $(TARGET) release/
	@echo "Готово! Смотри папку release/"
endif

# Линковка
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Генерация MOC файлов
MainWindow.moc.cpp: $(SRC_DIR)/MainWindow.h
	$(MOC) $< -o $@

# Компиляция .cpp файлов
main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/MainWindow.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

MainWindow.o: $(SRC_DIR)/MainWindow.cpp $(SRC_DIR)/MainWindow.h $(SRC_DIR)/Calculator.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

Calculator.o: $(SRC_DIR)/Calculator.cpp $(SRC_DIR)/Calculator.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

MainWindow.moc.o: MainWindow.moc.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Очистка
clean:
	rm -f $(OBJECTS) $(MOC_SOURCES) $(TARGET) calculator calculator.exe
	rm -rf release/

# Пересборка
rebuild: clean all

.PHONY: all clean rebuild
