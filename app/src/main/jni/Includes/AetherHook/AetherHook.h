/*
MIT License

Copyright (c) 2025 Qwanwin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef AETHER_HOOK_H
#define AETHER_HOOK_H

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#ifndef AETHER_HOOK_LOG_TAG
#define AETHER_HOOK_LOG_TAG "AetherHook"
#endif

/**
 * @brief Main namespace for AetherHook.
 *
 * AetherHook is a lightweight hooking library for Android that supports:
 *  - PLT hooking for shared libraries
 *  - Inline hooking for native functions
 *
 * Supported architectures:
 *  - ARM32 (armeabi-v7a)
 *  - ARM64 (arm64-v8a)
 */
namespace AetherHook {

    /**
     * @brief Initialize internal state.
     *
     * Call this once before using any other API.
     * This sets up internal flags, containers, and safety checks.
     */
    void initialize();

    /**
     * @brief Enable or disable debug logging.
     *
     * When enabled, extra logs will be printed to logcat
     * to help trace hook installation and execution.
     *
     * @param enable true to enable debug logs, false to disable.
     */
    void enable_debug(bool enable);

    /**
     * @brief Get library version string.
     *
     * @return Null-terminated version string.
     */
    const char* version();

    /**
     * @brief Print an info-level log message.
     *
     * @param fmt printf-style format string.
     * @param ... Arguments referenced by the format string.
     */
    void logi(const char* fmt, ...);

    /**
     * @brief Print a debug-level log message.
     *
     * This log will only appear when debug mode is enabled.
     *
     * @param fmt printf-style format string.
     * @param ... Arguments referenced by the format string.
     */
    void logd(const char* fmt, ...);

    /**
     * @brief Print an error-level log message.
     *
     * @param fmt printf-style format string.
     * @param ... Arguments referenced by the format string.
     */
    void loge(const char* fmt, ...);

    /**
     * @brief Apply all registered hooks.
     *
     * Call this after registering hooks and after the target
     * library or code is already loaded into memory.
     *
     * @param sync Reserved for future use (currently ignored).
     * @return 0 on success, -1 on failure.
     */
    int refresh(int sync = 0);

    /**
     * @brief PLT hooking API.
     *
     * These functions replace dynamically linked symbols
     * by patching entries in the Global Offset Table.
     */
    namespace PLT {

        /**
         * @brief Register a PLT hook.
         *
         * The hook will be applied to any shared library whose
         * path matches the given regex and exports the symbol.
         *
         * @param pathname_regex POSIX regex matching library path
         *                       (example: ".*libc.*\\.so$").
         * @param symbol Name of the function symbol to hook.
         * @param new_func Pointer to the replacement function.
         * @param old_func_out Optional pointer to receive the original function.
         *
         * @return 0 if registered successfully, -1 on error.
         */
        int register_hook(const char *pathname_regex,
                          const char *symbol,
                          void *new_func,
                          void **old_func_out = nullptr);

        /**
         * @brief Apply all registered PLT hooks.
         *
         * Usually called internally by refresh(), but can be
         * triggered manually if needed.
         */
        void apply_all_hooks();

        /**
         * @brief Remove a registered PLT hook.
         *
         * This marks the hook as inactive. Restoring the original
         * GOT entry is not guaranteed in the current implementation.
         *
         * @param pathname_regex Regex used during registration.
         * @param symbol Symbol name used during registration.
         *
         * @return 0 on success, -1 if the hook was not found.
         */
        int remove_hook(const char *pathname_regex,
                        const char *symbol);
    }

    /**
     * @brief Inline hooking API.
     *
     * Inline hooks work by patching the first instructions
     * of a function and redirecting execution.
     */
    namespace Inline {

        /**
         * @brief Register an inline hook.
         *
         * A trampoline will be created so the original function
         * can still be called safely.
         *
         * @param target_addr Address of the function to hook.
         * @param new_func Pointer to the replacement function.
         * @param old_func_out Optional pointer to receive trampoline address.
         *
         * @return 0 on success, -1 on failure or unsupported architecture.
         */
        int register_hook(void *target_addr,
                          void *new_func,
                          void **old_func_out = nullptr);

        /**
         * @brief Apply all registered inline hooks.
         */
        void apply_all_hooks();

        /**
         * @brief Remove an inline hook and restore original code.
         *
         * This attempts to restore the original instructions
         * and free any allocated trampoline memory.
         *
         * @param target_addr Address of the hooked function.
         * @return 0 on success, -1 on failure.
         */
        int remove_hook(void *target_addr);
    }

} // namespace AetherHook

#endif // AETHER_HOOK_H