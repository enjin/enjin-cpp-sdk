# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/), and this project adheres to
[Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [1.0.0.2002] - 2023-04-11

- Added `GetAssetsFromProjects` to `IProjectSchema`.
- Added `GetBalancesFromProjects` to `ISharedSchema`.

## [1.0.0.2001] - 2023-01-02

### Added

- Added `UpdateName` request to `IProjectSchema`.

### Fixed

- Fixed GraphQL template argument type for `BridgeClaimAsset`.

## [1.0.0.2000] - 2022-07-18

### Added

- Added `JsonValue` class.
- Added `JsonUtils` utility class.
- Added `EnumUtils` utility class.
- Added `to_json()` member-function to `ISerializable`.
- Added reauthentication features to `ProjectClient`.
- Added `close()` and `is_closed()` member-functions to `ClientMiddleware`.

### Changed

- Enums and constant expressions now use pascal case instead of upper-snake-case for their naming convention.
- Renamed `DEL` value in `HttpMethod` to `Delete`.
- Renamed `ERR` value in `LogLevel` to `Error`.
- Renamed `AssetSort` to `AssetSortInput`.
- Renamed `Melt` to `MeltInput`.
- Renamed `PaginationOptions` to `PaginationInput`.
- Renamed `Request` to `Transaction`.
- Renamed `RequestState` to `TransactionState`.
- Renamed `RequestType` to `TransactionType`.
- Renamed `Trade` to `TradeInput`.
- Renamed `TransactionSort` to `TransactionSortInput`.
- Renamed `Transfers` to `TransferInput`.
- Renamed `GetRequest` to `GetTransaction`.
- Renamed `GetRequests` to `GetTransactions`.
- Renamed `ProjectTransactionRequestArguments` to `TransactionRequestArguments`.
- Renamed `TrustedPlatformMiddleware` to `ClientMiddleware`.
- Moved `AssetTransferFeeSettingsInput` to its own header file.
- Moved `HttpMethod` to its own header file.
- Moved `LogLevel` to its own header file.
- `HttpRequest` now uses setter member-functions instead of a builder.
- Getters in `HttpRequest` now return an optional.
- Builders are now nested in the classes they are implemented for.
- Build function in builder for `PusherEventService` now returns a unique-pointer.
- Moved Enjin host URI expressions in EnjinHosts.hpp into a utility class named `EnjinHosts`.
- Changed the type of value contained within the optional for `AssetVariant::get_variant_metadata()` from a string
  to `JsonValue`.
- Changed the type of value contained within the optional for `TransactionEvent::get_inputs()` from a vector of strings
  to a vector of type `JsonValue`.
- Changed the type of value contained within the optional for `TransactionEvent::get_non_indexedinputs()` from a vector
  of strings to a vector of type `JsonValue`.
- Changed the type of value contained within the optional for `TransactionEvent::get_indexed_inputs()` from a vector of
  strings to a vector of type `JsonValue`.
- Changed the type of value contained within the optional for `TransactionLog::get_data()` from a vector of strings to a
  vector of type `JsonValue`.
- Changed the type of value contained within the optional for `TransactionLog::get_topics()` from a vector of strings to
  a vector of type `JsonValue`.
- Changed methods to use pass-by-value instead of pass-by-reference where appropriate.
- Moved functionality of `TrustedPlatformHandler` over to `ClientMiddleware`.
- Copy and move constructors for `PlayerClient`, `ProjectClient`, and `PusherEventService` are now explicitly deleted.
- Constructors for schema classes now take a unique-pointer for an HTTP client instead of a middleware.
- The future returned by `PusherEventService::shutdown()` no longer completes exceptionally if the function is called
  prior to starting the service.
- The destructor for `PusherEventService` now attempts to shut down the service.
- Argument interfaces for requests no longer override parent functions to access internal implementations.
- Argument interfaces for requests now use static-cast instead of dynamic-cast for their chaining functions.
- Content-Type header for `HttpRequest` is now stored in its headers set.

### Removed

- Removed internal argument implementation classes.
- Removed class `LoggerImpl` from public space.

### Fixed

- `ClientMiddleware` now checks if its HTTP client is null.
- Added template specializations of `BalanceFragmentArguments` for `GetPlayer`, `GetPlayers`, `GetWallet`,
  and `GetWallets` requests.

## [1.0.0.1006] - 2022-07-05

### Added

- Added `GOERLI` to `EnjinHosts.hpp`.

### Removed

- Removed `KOVAN` from `EnjinHosts.hpp`.

## [1.0.0.1005] - 2022-05-23

### Added

- Added arguments and fields to `Transaction.gql` template file for getting the wallet address.
- Added arguments and fields to `Wallet.gql` template file for getting balances and transactions.
- Added `set_with_transaction_wallet_address` member-function to `TransactionFragmentArguments`.
- Added `set_wallet_balance_filter`, `set_with_wallet_balances`, and `set_with_wallet_transaction` member-functions
  to `WalletFragmentArguments`.
- Added getters for balances and transactions to `Wallet` model.

### Changed

- Refactored `Balance`, `Player`, `Request`, and `Wallet` models to use pimpl idiom.
- Changed name of member-function `set_asset_id_format` in `TransactionFragmentArguments`
  to `set_transaction_asset_id_format`.
- `WalletFragmentArguments` now implements `BalanceFragmentArguments` and `TransactionFragmentArguments`.

### Fixed

- Fixed issue with argument interfaces not serializing data from parent argument interfaces.
- Fixed missing equality operator in `ProjectTransactionRequestArguments`.

## [1.0.0.1004] - 2022-04-25

### Changed

- Removed `set_project_uuid` and `set_project_uuid_in` member-functions from `BalanceFilter`.

## [1.0.0.1003] - 2022-04-11

### Changed

- `GetWallets` query in project schema no longer implements `PaginationArguments`.

### Fixed

- Fixed typo for `result` in `GetWallets.gql` template file for project schema.

## [1.0.0.1002] - 2022-03-01

### Changed

- Updated path to template generation command in root CMakeLists file.
- Updated regular expression used by `TemplateLoader` to match a wider range of characters leading to the "schemas"
  folder.

### Fixed

- Fixed package installation procedure in root CMakeLists file.

## [1.0.0.1001] - 2021-11-09

### Added

- Added [Enjin Bridge mutations](https://docs.enjin.io/enjin-api/sending-and-receiving-requests/enjin-bridge) for
  project and player schemas.
- Added `get_asset` member-function to `Request`.
- Added `set_asset_id_format` method to `TransactionFragmentArguments`.

### Changed

- The asset for transactions is now included in returned `Request` models when using `set_with_asset_data()` in requests
  which inherit `TransactionFragmentArguments`.

## [1.0.0.1000] - 2021-09-27

### Added

- Initial alpha release.

[Unreleased]: https://github.com/enjin/enjin-cpp-sdk/compare/1.0.0.2002...HEAD

[1.0.0.2002]: https://github.com/enjin/enjin-cpp-sdk/compare/1.0.0.2001...1.0.0.2002

[1.0.0.2001]: https://github.com/enjin/enjin-cpp-sdk/compare/1.0.0.2000...1.0.0.2001

[1.0.0.2000]: https://github.com/enjin/enjin-cpp-sdk/compare/1.0.0.1006...1.0.0.2000

[1.0.0.1006]: https://github.com/enjin/enjin-cpp-sdk/compare/1.0.0.1005...1.0.0.1006

[1.0.0.1005]: https://github.com/enjin/enjin-cpp-sdk/compare/1.0.0.1004...1.0.0.1005

[1.0.0.1004]: https://github.com/enjin/enjin-cpp-sdk/compare/1.0.0.1003...1.0.0.1004

[1.0.0.1003]: https://github.com/enjin/enjin-cpp-sdk/compare/1.0.0.1002...1.0.0.1003

[1.0.0.1002]: https://github.com/enjin/enjin-cpp-sdk/compare/1.0.0.1001...1.0.0.1002

[1.0.0.1001]: https://github.com/enjin/enjin-cpp-sdk/compare/1.0.0.1000...1.0.0.1001

[1.0.0.1000]: https://github.com/enjin/enjin-cpp-sdk/releases/tag/1.0.0.1000